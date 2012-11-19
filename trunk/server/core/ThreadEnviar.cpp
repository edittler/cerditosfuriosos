#include "ThreadEnviar.h"

ThreadEnviar::ThreadEnviar(Socket* socket) {
	this->socket = socket;
}

ThreadEnviar::~ThreadEnviar() {
	while (!mensajes.estaVacia()) {
		RespuestaServer* m = mensajes.obtenerFrente();
		delete m;
	}
}

void ThreadEnviar::agregarMensaje(RespuestaServer* mensaje) {
	this->mensajes.encolar(mensaje);
}

void* ThreadEnviar::run() {
	while (!terminado) {
		RespuestaServer* m = mensajes.obtenerFrente();
		this->socket->enviar(*m);
		delete m;
	}

	return NULL;
}

