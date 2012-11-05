#include "ThreadListener.h"

ThreadListener::ThreadListener() { }

ThreadListener::ThreadListener(Server* server) {
	this->server = server;
}

ThreadListener::~ThreadListener() { }

void* ThreadListener::run() {
	while (server->encendido) {
		int fd = server->socket->aceptar();

		if (fd < 0)
			continue;

		server->registrarCliente(new ThreadCliente(fd));
	}
	return NULL;
}
