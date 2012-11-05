#include "SocketCliente.h"

SocketCliente::SocketCliente() : Socket() { }

SocketCliente::SocketCliente(int fd) : Socket(fd) { }

SocketCliente::~SocketCliente() { }

void SocketCliente::conectar(const char* server, unsigned short int port) {
	// busco la ip del servidor
	hostent* r = gethostbyname(server);
	in_addr* server_adress;
	if (r == NULL) {
		// TODO flag server invalido
		return;
	}
	server_adress = (in_addr*) r->h_addr;

	// crea informacion del servidor
	sockaddr_in server_info;
	memset(&server_info, 0, sizeof(server_info));
	server_info.sin_family = AF_INET;
	server_info.sin_addr = *server_adress;
	server_info.sin_port = htons(port);

	if (connect(fd, (sockaddr*) &server_info, sizeof(server_info)) < 0) {
		// TODO flag conect
	}
}


