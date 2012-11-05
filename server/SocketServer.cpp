#include "SocketServer.h"

SocketServer::SocketServer() : Socket() { }

SocketServer::SocketServer(int fd) : Socket(fd) { }

SocketServer::~SocketServer() { }

void SocketServer::enlazar(unsigned int port) {
	sockaddr_in info;
	memset(&info, 0, sizeof(info));
	info.sin_family = AF_INET;
	info.sin_port = htons(port);
	info.sin_addr.s_addr = INADDR_ANY;

	if (bind(fd, (sockaddr*) &info, sizeof(info)) < 0) {
		error = true;
	}
}

void SocketServer::escuchar(unsigned int maxWait) {
	if (listen(fd, maxWait) < 0) {
		error = false;
	}
}

int SocketServer::aceptar() {
	sockaddr_in client_info;
	memset(&client_info, 0, sizeof(client_info));
	unsigned int client_info_len = sizeof(client_info);
	int nuevoFd = accept(fd, (sockaddr*) &client_info, &client_info_len);

	if (nuevoFd == 0) {  // comunicacion finalizada
		error = false;
	} if (nuevoFd < 0) {  // comunicacion fallo
		error = false;
	}
	return nuevoFd;
}

