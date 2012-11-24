#include "ThreadPartida.h"
#include "MensajeServer.h"
#include "../../common/communication/ConstantesClientServer.h"

ThreadPartida::ThreadPartida(Partida* partida, ThreadCliente* cliente) {
	this->partida = partida;
	this->agregarJugador(cliente);
}

ThreadPartida::~ThreadPartida() {
	// TODO Auto-generated destructor stub
}

void ThreadPartida::comenzarPartida() {
	ClientesConectados::iterator it;
	// TODO crear y enviar MensajeServer para iniciar partida
	for (it = jugadores.begin(); it != jugadores.end(); ++it) {
		// TODO enviar XML a clientes, agregar metodos enviar y recibir a ThreadCliente
//		(*it)->enviar(*m);
	}
}

bool ThreadPartida::unirseAPartida(ThreadCliente* cliente) {
	if (partida->comienzo())  // ya hay la cantidad de jugadores necesarios
		return false;

	if (partida->getEstado() == CREANDO) {  // se esta creando.
		return this->agregarJugador(cliente);
	}

	if (partida->getEstado() == ESPERANDO_JUGADOR) {  // esperando a nuevo jugador
		// TODO Enviar XML actual del nivel.
		return this->agregarJugador(cliente);
	}
	return false;
}

void ThreadPartida::abandonarPartida(ThreadCliente* cliente) {
	this->eliminarJugador(cliente);

	if (partida->getEstado() ==  EJECUTANDO)
		partida->setEstado(PAUSADO);
}

void ThreadPartida::pausarPartida() {
	ClientesConectados::iterator it;
	for (it = jugadores.begin(); it != jugadores.end(); ++it) {
		// TODO crear y enviar MensajeServer para pausar
	}
}

void ThreadPartida::finalizarPartida() {
	ClientesConectados::iterator it;
	for (it = jugadores.begin(); it != jugadores.end(); ++it) {
		// TODO crear y enviar MensajeServer para finalizar partida.
	}
}

void* ThreadPartida::run() {
	while (!partida->finalizo()) {
		switch (partida->getEstado()) {
			case CREANDO: {
				std::cout << "ThreadPartida, estado = CREANDO" << std::endl;
				if (partida->comienzo()) {
					this->comenzarPartida();
					partida->setEstado(EJECUTANDO);
				}
				break; }

			case EJECUTANDO: {
				std::cout << "ThreadPartida, estado = EJECUTANDO" << std::endl;
				// procesa mensajes recibidos
				ClientesConectados::iterator it;
				// procesa mensajes de cada cliente conectado
				for (it = this->jugadores.begin(); it != jugadores.end(); ++it) {
					// procesa hasta un maximo de mensajes por cliente
					for (int i = 0; i < MAX_MSJ_PROCESADOS; ++i) {

						// FIXME en lugar de leer de los ThreadRecibir se deberia
						// leer de la cola de eventos guardada en el ThreadCliente

						Mensaje* m = (*it)->recibir();
						if (m == NULL)
							break;

						// el mensaje recibido debe ser del tipo MensajeCliente
						MensajeCliente* msj = dynamic_cast<MensajeCliente*>(m);
						if (msj == NULL)
							continue;

						// solo procesa el comando EVENTO, los demas tipos de comandos
						// son procesados en ThreadCliente.
						if (msj->getComando()) {
							Evento e = msj->getEvento();
							switch (e.getTipoEvento()) {
								case E_PEDIDO_LANZAR_DISPARO: {
									// TODO crear disparo en Escenario.
									// TODO enviar E_LANZAR_DISPARO a demas clientes conetados
									Evento nuevoEvento(e.getTipoDisparo(), e.getPunto(), e.getVelocidad());
									MensajeServer* r = new MensajeServer(nuevoEvento);
									break; }
								default:
									// el unico mensaje proveniente del cliente que es procesado es el
									// pedido de disparo. No deberia llegar otro tipo de mensaje,
									// si llegara a suceder se ignora.
									break;
							}
						}
					}
				}

				// TODO corre tick
				// TODO enviar mensajes posteriores a ticks (Lanzamiento Pajaro, fin de partida)
				break; }

			case ESPERANDO_JUGADOR: {
				std::cout << "ThreadPartida, estado = ESPERANDO_JUGADOR" << std::endl;
				// TODO esperar jugador faltante y renaudar partida.
				this->partida->setEstado(EJECUTANDO);
				break;}

			case PAUSADO: {
				std::cout << "ThreadPartida, estado = PAUSADO" << std::endl;
				// TODO enviar notificacion de pausado a todos los clientes.
				this->pausarPartida();
				// TODO solo se pausaria una partida si falta un jugador se pasa al estado
				// correspondiente
				this->partida->setEstado(ESPERANDO_JUGADOR);
				break; }

			case FINALIZADO: {
				std::cout << "ThreadPartida, estado = FINALIZADO" << std::endl;
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
	return this->partida->getId();
}

std::string ThreadPartida::getNombrePartida() const {
	return this->partida->getNombre();
}

bool ThreadPartida::agregarJugador(ThreadCliente* cliente) {
	// obtengo id de jugador que no es manejado por ningun cliente
	unsigned int id = this->partida->getIdJugadorNoConectado();
	if (id != 0) {
		// asigno el id del jugador al cliente
		cliente->asignarJugador(id);
		jugadores.push_back(cliente);
		return true;
	}
	return false;
}

bool ThreadPartida::eliminarJugador(ThreadCliente* cliente) {
	ClientesConectados::iterator it;
	for (it = jugadores.begin(); it != jugadores.end(); ++it) {
		if ((*it)->getJugadorAsignado() == cliente->getJugadorAsignado()) {
			jugadores.remove(cliente);
			// TODO liberar id jugador en el escenario.
		}
	}
	return false;
}
