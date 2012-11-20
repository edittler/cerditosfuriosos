#include "ThreadRecibir.h"

ThreadRecibir::ThreadRecibir(Socket* socket) {
	this->socket = socket;
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
		this->socket->recibir(*m);
		mensajes.encolar(m);
	}

	return NULL;
}



