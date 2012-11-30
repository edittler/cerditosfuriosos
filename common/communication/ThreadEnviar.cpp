#include "ThreadEnviar.h"

ThreadEnviar::ThreadEnviar(Socket& socket) : socket(socket) {
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
		// Si el socket está desconectado, activo flag terminado
		if (!socket.estaConectado()) {
			terminado = true;
			break;
		}
		if (!mensajes.estaVacia()) {
			Mensaje* m = mensajes.obtenerFrente();
			this->socket.enviar(*m);
			delete m;
		}
	}
	return NULL;
}
