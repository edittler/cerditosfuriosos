#include "ThreadRecibirCliente.h"

ThreadRecibirCliente::ThreadRecibirCliente(Socket& socket) : socket(socket) {
	this->terminado = false;
}

ThreadRecibirCliente::~ThreadRecibirCliente() {
	this->terminado = true;
	while (!mensajes.estaVacia()) {
		Mensaje* m = mensajes.obtenerFrente();
		delete m;
	}
}

Mensaje* ThreadRecibirCliente::getMensaje() {
	if (!mensajes.estaVacia())
		return this->mensajes.obtenerFrente();
	return NULL;
}

void* ThreadRecibirCliente::run() {
	while (!terminado) {
		Mensaje* m = new MensajeServer();
		this->socket.recibir(*m);

		// valido que no se haya cerrado la conexion
		if (!this->socket.estaConectado()) {
			this->terminado = true;
			break;
		}
		mensajes.encolar(m);
	}
	return NULL;
}

