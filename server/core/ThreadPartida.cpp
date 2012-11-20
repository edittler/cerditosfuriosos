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

void ThreadPartida::unirseAPartida(ThreadCliente* cliente) {
	if (partida->comienzo())  // ya hay la cantidad de jugadores necesarios
		return;

	if (partida->getEstado() == CREANDO) {  // se esta creando.
		this->agregarJugador(cliente);
	}

	if (partida->getEstado() == ESPERANDO_JUGADOR) {  // esperando a nuevo jugador
		this->agregarJugador(cliente);
	}

	// TODO se podria agregar logica extrea si no puede agregarse cliente a partida.
	// por ejemplo puede lanzarse una excepcion
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
				for (it = this->jugadores.begin(); it != jugadores.end(); ++it) {
					for (int i = 0; i < MAX_MSJ_PROCESADOS; ++i) {
						// TODO implementar
						// recibe mensaje si es NULL break;
						// si necesita reenviar a demas jugadores encolar para enviar
						// si se desconecto jugador pausar partida
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
