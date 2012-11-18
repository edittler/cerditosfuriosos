#include "ThreadPartida.h"

ThreadPartida::ThreadPartida(Partida* partida, ThreadCliente* cliente) {
	this->partida = partida;
	this->jugadores.push_back(cliente);
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
				/* TODO Verifico si la cantidad de clientes conectados
				 * es igual a la cantidad q requiere el mundo.
				 * Si es así, envío el primer nivel y cambio el estado a
				 * EJECUTANDO.
				 */
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
