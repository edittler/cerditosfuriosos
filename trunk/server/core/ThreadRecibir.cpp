#include "ThreadRecibir.h"

ThreadRecibir::ThreadRecibir(Socket* socket) {
	this->socket = socket;
}

ThreadRecibir::~ThreadRecibir() {
	while (!mensajes.estaVacia()) {
		MensajeCliente* m = mensajes.obtenerFrente();
		delete m;
	}
}

MensajeCliente* ThreadRecibir::getMensaje() {
	return this->mensajes.obtenerFrente();
}

void* ThreadRecibir::run() {
	while (!terminado) {
		MensajeCliente* m = new MensajeCliente();
		this->socket->recibir(*m);
		mensajes.encolar(m);
	}

	return NULL;
}



