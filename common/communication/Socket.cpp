#include "Socket.h"

Socket::Socket() {
	error = false;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		// TODO flag creacion
	}
}

Socket::Socket(int fd) {
	error = false;
	this->fd = fd;
}

Socket::~Socket() {
	close(this->fd);
}

void Socket::enviar(Mensaje* mensaje) {
	std::string s = mensaje->serealizar();
	size_t parcial = 0, enviado,
			total = s.length();

	parcial = send(fd, s.c_str(), total, 0);
	while (parcial < total) {
		s = s.substr(parcial);  // crea substring con porcion del mensaje no enviada.
		enviado = send(fd, s.c_str(), total, 0);
		parcial = enviado;
		total = s.length();
	}
}

void Socket::recibir(Mensaje* mensaje) {
	bool finalizado = false;
	std::string s;
	char* buffer =  new char[MAX_LENGTH_MESSAGE];

	while (!finalizado) {
		memset(buffer, 0, MAX_LENGTH_MESSAGE);
		int r = recv(fd, buffer, MAX_LENGTH_MESSAGE - 1, 0);

		if (r == 0)  // finalizo comunicacion
			break;

		if (r < 0)  // error comunicacion
			break;

		s.append(buffer);
		if (s.at(s.length() - 1) == '\n')
			finalizado = true;
	}
	delete[] buffer;
	mensaje->deserealizar(s);
}

void Socket::desconectar() {
	if (shutdown(fd, SHUT_RDWR) < 0) {
		error = true;
	}
}

