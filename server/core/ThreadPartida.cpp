#include "ThreadPartida.h"
#include "MensajeServer.h"
#include "ConstantesClientServer.h"
#include "../modelo/ConstantesServer.h"
#include "Lock.h"
#include "log/Log.h"

ThreadPartida::ThreadPartida(Partida* partida, ThreadCliente* cliente) {
	this->partida = partida;
	this->agregarJugador(cliente);
}

ThreadPartida::~ThreadPartida() {
	// TODO Auto-generated destructor stub
}

void ThreadPartida::comenzarPartida() {
	Lock(this->mJugadores);
	ClientesConectados::iterator it;
	for (it = jugadores.begin(); it != jugadores.end(); ++it) {
		MensajeServer* m = new MensajeServer(MS_CARGAR_NIVEL);
		Lock(this->mPartida);
		m->set(this->partida->getXMLNivel());
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
		MensajeServer* m = new MensajeServer(MS_CARGAR_NIVEL);
		m->set(this->partida->getXMLNivel());
		return this->agregarJugador(cliente);
	}
	return false;
}

void ThreadPartida::abandonarPartida(ThreadCliente* cliente) {
	this->eliminarJugador(cliente);

	if (partida->getEstado() ==  EJECUTANDO) {
		Lock(this->mPartida);
		partida->setEstado(PAUSADO);
	}
}

void ThreadPartida::pausarPartida() {
	Lock(this->mJugadores);
	ClientesConectados::iterator it;
	for (it = jugadores.begin(); it != jugadores.end(); ++it) {
		MensajeServer* m = new MensajeServer(MS_PAUSAR_PARTIDA);
		(*it)->enviar(m);
	}
}

void ThreadPartida::finalizarPartida() {
	Lock(this->mJugadores);
	ClientesConectados::iterator it;
	for (it = jugadores.begin(); it != jugadores.end(); ++it) {
		// TODO crear y enviar MensajeServer para finalizar partida.
	}
}

void* ThreadPartida::run() {
	while (!partida->finalizo()) {
		switch (partida->getEstado()) {
			case CREANDO: {
				LOG_INFO("estado = CREANDO")
				Lock(this->mPartida);
				if (partida->comienzo()) {
					this->comenzarPartida();
					partida->setEstado(EJECUTANDO);
				}
				break; }

			case EJECUTANDO: {
				LOG_INFO("estado = EJECUTANDO")
				// procesa mensajes de cada cliente conectado
				this->procesarMensajesClientes();

				// Corre tick del escenario y envia mensaje E_CORRER_TICK
				this->partida->getNivel()->tick(SERVER_TICK_MSEG);
				ClientesConectados::iterator it;
				Evento e(E_CORRER_TICK);
				this->mJugadores.lock();
				MensajeServer* m = new MensajeServer(e);
				for (it = jugadores.begin(); it != jugadores.end(); ++it) {
					(*it)->enviar(m);
				}
				this->mJugadores.unlock();

				// procesa mensajes posteriores a ticks (Lanzamiento Pajaro, fin de partida)
				this->procesarMensajesParaClientes();
				break; }

			case ESPERANDO_JUGADOR: {
				LOG_INFO("estado = ESPERANDO_JUGADOR")
				// TODO esperar jugador faltante y renaudar partida.
				Lock(this->mPartida);
				this->partida->setEstado(EJECUTANDO);
				break;}

			case PAUSADO: {
				LOG_INFO("estado = PAUSADO")
				// TODO enviar notificacion de pausado a todos los clientes.
				this->pausarPartida();
				// TODO solo se pausaria una partida si falta un jugador se pasa al estado
				// correspondiente
				Lock(this->mPartida);
				this->partida->setEstado(ESPERANDO_JUGADOR);
				break; }

			case FINALIZADO: {
				LOG_INFO("estado = FINALIZADO")
				// TODO actualizar records
				// TODO enviar notificacion de finalizado a todos los clientes
				// en caso de que se necesario.
				break; }

			default:
				break;
		}
	}

	return NULL;
}

unsigned int ThreadPartida::getId() {
	Lock(this->mPartida);
	return this->partida->getId();
}

std::string ThreadPartida::getNombrePartida() const {
//	Lock(this->mPartida);
	return this->partida->getNombre();
}

bool ThreadPartida::agregarJugador(ThreadCliente* cliente) {
	// obtengo id de jugador que no es manejado por ningun cliente
	Lock(this->mPartida);
	unsigned int id = this->partida->getIdJugadorNoConectado();
	if (id != 0) {
		// asigno el id del jugador al cliente
		cliente->asignarJugador(id);
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
			jugadores.remove(cliente);
			Lock(this->mPartida);
			this->partida->setIdJugadorNoConectado(idADesconectar);
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
			if (!(*it)->hayEventos())
				break;

			// solo procesa el comando EVENTO, los demas tipos de comandos
			// son procesados en ThreadCliente.
			Evento e = (*it)->popEvento();
			switch (e.getTipoEvento()) {
				case E_PEDIDO_LANZAR_DISPARO: {
					// instancia disparo en escenario
					this->partida->getNivel()->lanzarHuevo(e.getTipoDisparo(),
							e.getPunto(), e.getVelocidad(), (*it)->getJugadorAsignado());

					// enviar E_LANZAR_DISPARO a TODOS los clientes conetados
					// (incluyendose a el mismo)
					Evento nuevoEvento(e.getTipoDisparo(), e.getPunto(), e.getVelocidad());
					MensajeServer* r = new MensajeServer(nuevoEvento);
					for (it = this->jugadores.begin(); it != jugadores.end(); ++it) {
						(*it)->enviar(r);
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
	for (int i = 0; i < MAX_MSJ_PROCESADOS; ++i) {
		// valido que haya eventos para procesar.
		Lock(this->mPartida);
		if (!this->partida->hayEventos())
			break;

		Evento e = this->partida->obtenerEvento();

		// informo del evento a todos los clientes conectados
		MensajeServer* m = new MensajeServer(e);
		Lock(this->mJugadores);
		ClientesConectados::iterator it;
		for (it = jugadores.begin(); it != jugadores.end(); ++it) {
			(*it)->enviar(m);
		}
	}
}
