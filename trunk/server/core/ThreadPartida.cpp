#include "ThreadPartida.h"

ThreadPartida::ThreadPartida(Partida* partida) {
	// TODO Auto-generated constructor stub
	this->partida = partida;
}

ThreadPartida::~ThreadPartida() {
	// TODO Auto-generated destructor stub
}

void ThreadPartida::comenzarPartida() {
	ClientesConectados::iterator it;
	for (it = jugadores.begin(); it != jugadores.end(); ++it) {
		// TODO enviar XML a clientes
	}
}

void ThreadPartida::finalizarPartida() {

}

void* ThreadPartida::run() {
	while (!partida->finalizo()) {
		switch (partida->getEstado()) {
			case CREANDO: {
				// TODO esperar a que se conectens mas clientes.
				break; }

			case EJECUTANDO: {
				// TODO recibir eventos de parte de los clientes conectados.
				// TODO enviar XML del escenario.
				break; }

			case PAUSADO: {
				// TODO enviar notificacion de pausado a todos los clientes.
				break; }

			case FINALIZADO: {
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
