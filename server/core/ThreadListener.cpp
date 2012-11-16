#include "ThreadListener.h"

ThreadListener::ThreadListener() { }

ThreadListener::ThreadListener(Server* server) {
	this->server = server;
}

ThreadListener::~ThreadListener() { }

void* ThreadListener::run() {
	while (server->encendido) {
		Socket* socket = server->socket->aceptarConexion();

		if (socket == NULL)
			continue;

		server->registrarCliente(new ThreadCliente(socket));
	}
	return NULL;
}
