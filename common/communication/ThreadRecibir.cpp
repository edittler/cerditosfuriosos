#include "ThreadRecibir.h"

ThreadRecibir::ThreadRecibir(Socket& socket) : socket(socket) {
	this->terminado = false;
}

ThreadRecibir::~ThreadRecibir() {
	this->terminado = true;
	while (!mensajes.estaVacia()) {
		Mensaje* m = mensajes.obtenerFrente();
		delete m;
	}
}

Mensaje* ThreadRecibir::getMensaje() {
	if (!mensajes.estaVacia())
		return this->mensajes.obtenerFrente();
	return NULL;
}

void* ThreadRecibir::run() {
	while (!terminado) {
		Mensaje* m = new MensajeCliente();
		this->socket.recibir(*m);

		// valido que no se haya cerrado la conexion
		if (this->socket.estaConectado()) {
			this->terminado = true;
			break;
		}
		mensajes.encolar(m);
	}
	return NULL;
}
