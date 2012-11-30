// Header Includes
#include "ThreadPartida.h"

// Common Project Includes.
#include "MensajeServer.h"
#include "ConstantesClientServer.h"
#include "Lock.h"
#include "Log.h"

// Server Project Includes.
#include "../modelo/ConstantesServer.h"

ThreadPartida::ThreadPartida(Partida* partida, ThreadCliente* cliente) {
	this->conectado = true;
	this->partida = partida;
	this->agregarJugador(cliente);
}

ThreadPartida::~ThreadPartida() {
	delete this->partida;
}

void ThreadPartida::finalizar() {
	this->conectado = false;
}

void ThreadPartida::comenzarPartida() {
	Lock(this->mJugadores);
	ClientesConectados::iterator it;
	for (it = jugadores.begin(); it != jugadores.end(); ++it) {
		Mensaje* m = new MensajeServer(this->partida->getXMLNivel());
		Lock(this->mPartida);
		(*it)->enviar(m);
	}
}

bool ThreadPartida::unirseAPartida(ThreadCliente* cliente) {
	Lock(this->mPartida);
	if (partida->comienzo())  // ya hay la cantidad de jugadores necesarios
		return false;

	if (partida->getEstado() == CREANDO) {  // se esta creando.
		return this->agregarJugador(cliente);
	}

	if (partida->getEstado() == ESPERANDO_JUGADOR) {  // esperando a nuevo jugador
		Mensaje* m = new MensajeServer(this->partida->getXMLNivel());
		return this->agregarJugador(cliente);
	}
	return false;
}

void ThreadPartida::abandonarPartida(ThreadCliente* cliente) {
	this->eliminarJugador(cliente);
	Lock(this->mPartida);
	if (partida->getEstado() ==  EJECUTANDO) {
		partida->setEstado(PAUSADO);
	}
}

void ThreadPartida::pausarPartida() {
	Lock(this->mJugadores);
	ClientesConectados::iterator it;
	for (it = jugadores.begin(); it != jugadores.end(); ++it) {
		Mensaje* m = new MensajeServer(MS_PAUSAR_PARTIDA);
		(*it)->enviar(m);
	}
}

void ThreadPartida::finalizarPartida() {
	Lock(this->mJugadores);
	ClientesConectados::iterator it;
	for (it = jugadores.begin(); it != jugadores.end(); ++it) {
		Mensaje* m = new MensajeServer(MS_FINALIZAR_PARTIDA);
		(*it)->enviar(m);
	}
}

void* ThreadPartida::run() {
	while (!partida->finalizo() && this->conectado) {
		switch (partida->getEstado()) {
			case CREANDO: {
//				LOG_INFO("estado = CREANDO")
				Lock(this->mPartida);
				if (partida->comienzo()) {
					this->comenzarPartida();
					partida->setEstado(EJECUTANDO);
				}
				break; }

			case EJECUTANDO: {
//				LOG_INFO("estado = EJECUTANDO")
				// procesa mensajes de cada cliente conectado
				this->procesarMensajesClientes();

				// Corre tick del escenario y envia mensaje E_CORRER_TICK
				mPartida.lock();
				this->partida->getNivel()->tick(SERVER_TICK_MSEG);
				mPartida.unlock();
				ClientesConectados::iterator it;
				Evento e(E_CORRER_TICK);
				this->mJugadores.lock();
				for (it = jugadores.begin(); it != jugadores.end(); ++it) {
					Mensaje* m = new MensajeServer(e);
					(*it)->enviar(m);
				}
				this->mJugadores.unlock();

				// procesa mensajes posteriores a ticks (Lanzamiento Pajaro, fin de partida)
				this->procesarMensajesParaClientes();
				break; }

			case ESPERANDO_JUGADOR: {
//				LOG_INFO("estado = ESPERANDO_JUGADOR")
				Lock(this->mPartida);
				if (partida->comienzo()) {
					partida->setEstado(EJECUTANDO);
				}
				break; }

			case PAUSADO: {
//				LOG_INFO("estado = PAUSADO")
				this->pausarPartida();
				Lock(this->mPartida);
				this->partida->setEstado(ESPERANDO_JUGADOR);
				break; }

			case FINALIZADO: {
//				LOG_INFO("estado = FINALIZADO")
				// TODO actualizar records
				this->finalizarPartida();
				break; }

			default:
				break;
		}
	}

	LOG_INFO("finalizando...")

	// si se desconecto la partida avisa a los clientes
	// que finalizo sin actualizar records.
	if (!this->conectado) {
		this->finalizarPartida();
	}

	return NULL;
}

unsigned int ThreadPartida::getId() {
	Lock(this->mPartida);
	return this->partida->getId();
}

std::string ThreadPartida::getNombrePartida() {
	Lock(this->mPartida);
	return this->partida->getNombre();
}

bool ThreadPartida::agregarJugador(ThreadCliente* cliente) {
	// obtengo id de jugador que no es manejado por ningun cliente
	Lock(this->mPartida);
	unsigned int id = this->partida->getIdJugadorNoConectado();
	if (id != 0) {
		// asigno el id del jugador al cliente
		cliente->asignarJugador(id);
		this->partida->setIdJugadorConectado(id);
		Lock(this->mJugadores);
		jugadores.push_back(cliente);
		return true;
	}
	return false;
}

bool ThreadPartida::eliminarJugador(ThreadCliente* cliente) {
	Lock(this->mJugadores);
	ClientesConectados::iterator it;
	for (it = jugadores.begin(); it != jugadores.end(); ++it) {
		unsigned int idADesconectar = cliente->getJugadorAsignado();
		if ((*it)->getJugadorAsignado() == idADesconectar) {
			it = jugadores.erase(it);
			Lock(this->mPartida);
			this->partida->setIdJugadorNoConectado(idADesconectar);
			return true;
		}
	}
	return false;
}

void ThreadPartida::procesarMensajesClientes() {
	ClientesConectados::iterator it;
	Lock(this->mJugadores);
	for (it = this->jugadores.begin(); it != jugadores.end(); ++it) {
		// procesa hasta un maximo de mensajes por cliente
		for (int i = 0; i < MAX_MSJ_PROCESADOS; ++i) {
			// si no hay eventos continuo con proximo cliente
			LOG_INFO("\tchequea evento hayEventos")
			if (!(*it)->hayEventos())
				break;

			LOG_INFO("\tprocesa evento de cola")

			// solo procesa el comando EVENTO, los demas tipos de comandos
			// son procesados en ThreadCliente.
			Evento e = (*it)->desencolarEvento();
			switch (e.getTipoEvento()) {
				case E_PEDIDO_LANZAR_DISPARO: {
					Lock(this->mPartida);
					// instancia disparo en escenario
					this->partida->getNivel()->lanzarHuevo(e.getTipoDisparo(),
							e.getPunto(), e.getVelocidad(), (*it)->getJugadorAsignado());

					// enviar E_LANZAR_DISPARO a TODOS los clientes conetados
					// (incluyendose a el mismo)
					Evento nuevoEvento(e.getTipoDisparo(), e.getPunto(), e.getVelocidad());
					ClientesConectados::iterator it2;
					for (it2 = this->jugadores.begin(); it2 != jugadores.end(); ++it2) {
						Mensaje* r = new MensajeServer(nuevoEvento);
						(*it2)->enviar(r);
					}

					break; }
				default:
					// el unico mensaje proveniente del cliente que es procesado es el
					// pedido de disparo. No deberia llegar otro tipo de mensaje,
					// si llegara a suceder se ignoraria.
					break;
			}
		}
	}
}

void ThreadPartida::procesarMensajesParaClientes() {
	Lock(this->mPartida);
	// valida finalizacion de partida
	if (this->partida->getNivel()->finalizoPartida()) {
		Evento e(E_FIN_NIVEL);

		// informo del evento a todos los clientes conectados
		Lock(this->mJugadores);
		ClientesConectados::iterator it;
		for (it = jugadores.begin(); it != jugadores.end(); ++it) {
			Mensaje* m = new MensajeServer(e);
			(*it)->enviar(m);
		}
	}

	for (int i = 0; i < MAX_MSJ_PROCESADOS; ++i) {
		// valido que haya eventos para procesar.
		if (!this->partida->hayEventos())
			break;

		Evento e = this->partida->obtenerEvento();

		// informo del evento a todos los clientes conectados
		Lock(this->mJugadores);
		ClientesConectados::iterator it;
		for (it = jugadores.begin(); it != jugadores.end(); ++it) {
			Mensaje* m = new MensajeServer(e);
			(*it)->enviar(m);
		}
	}
}
