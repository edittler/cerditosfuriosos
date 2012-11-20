#include "ThreadEnviar.h"

ThreadEnviar::ThreadEnviar(Socket* socket) {
	this->socket = socket;
	this->terminado = false;
}

ThreadEnviar::~ThreadEnviar() {
	this->terminado = true;
	while (!mensajes.estaVacia()) {
		Mensaje* m = mensajes.obtenerFrente();
		delete m;
	}
}

void ThreadEnviar::agregarMensaje(Mensaje* mensaje) {
	this->mensajes.encolar(mensaje);
}

void* ThreadEnviar::run() {
	while (!terminado) {
		if (!mensajes.estaVacia()) {
			Mensaje* m = mensajes.obtenerFrente();
			this->socket->enviar(*m);
			delete m;
		}
	}

	return NULL;
}

