#include "Socket.h"
#include <cstring>
#include <cerrno>
#include <csignal>

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>  // Para poder usar la funcion "gethostbyname"

#define MAX_LENGTH_MESSAGE 1024

Socket::Socket(Puerto puerto) {
	this->inicializar();
	this->puerto = puerto;

	this->fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->fd == -1) {
		// TODO Flag o expcepcion?
	}
}

Socket::Socket(int fd) {
	this->inicializar();
	this->fd = fd;
	this->conectado = true;
}

void Socket::inicializar() {
	this->fd = 0;
	this->puerto = 0;
	this->enlazado = false;
	this->conectado = false;
}

Socket::~Socket() {
	close(this->fd);
}

bool Socket::enlazar() {
	// Inicializo la estructura serv_addr
	std::memset((char *)&(this->direccion), 0, sizeof(this->direccion));
	this->direccion.sin_family = AF_INET;  // Tipo internet
	this->direccion.sin_port = htons(this->puerto);
	this->direccion.sin_addr.s_addr = INADDR_ANY;  // Direccion de la propia PC
	// Enlazo la dirección al socket
	int r = bind(this->fd, (struct sockaddr*)&(this->direccion),
			(socklen_t)sizeof(struct sockaddr));
	if (r == -1)
		return false;
	this->enlazado = true;
	this->conectado = true;
	return true;
}

bool Socket::escucharConexiones(int maxConexiones) {
	int r = listen(this->fd, maxConexiones);
	// Si retorna -1, hubo un error por lo que retorno false
	if (r == -1)
		return false;
	return true;
}

/* @brief Acepta una nueva conexión entrante y retorna un puntero al
 * socket remoto.
 */
Socket* Socket::aceptarConexion() {
	if (this->enlazado == false)
		return NULL;
	Socket* cli_sock = NULL;
	int cli_fd = 0;
	struct sockaddr_in cli_addr;
	unsigned int cli_size = (socklen_t) sizeof(cli_addr);
	// Acepto la conexion entrante
	cli_fd = accept(fd, (struct sockaddr *)&cli_addr, &cli_size);

	if (cli_fd > 0) {
		cli_sock = new Socket(cli_fd);
		std::memcpy(&cli_sock->direccion, &cli_addr, sizeof(cli_addr));
	}
	return cli_sock;
}

bool Socket::conectar(const std::string serverAddr) {
	// Si el socket ya se encuentra conectado, no realizo nada.
	if (conectado == true)
		return false;

	// Completamos la estructura con la dirección y puerto destino
	this->direccion.sin_family = AF_INET;  // Orden de bytes de la máquina
	this->direccion.sin_port = htons(puerto);  // short, Orden de bytes de la red
	// Convierto la direccion IP
	this->direccion.sin_addr.s_addr = inet_addr(serverAddr.c_str());
	long ip = (long) this->direccion.sin_addr.s_addr;
	// Si la conversion de la direccion no fue exitosa, retorno false.
	if (ip == -1) {
		return false;
	}
	memset(&(this->direccion.sin_zero), 0, 8);  // poner a cero el resto

	// Procedo a conectar el socket
	int r = connect(fd, (struct sockaddr*)&(this->direccion),
			sizeof(struct sockaddr));
	if (r == -1) {
		return false;
	}
	this->conectado = true;
	return true;
}

bool Socket::conectarPorNombre(const std::string serverAddr) {
	// Si el socket ya se encuentra conectado, no realizo nada.
	if (conectado == true)
		return false;

	struct hostent *he;
	he = gethostbyname(serverAddr.c_str());  // Obtener información del host
	if (he == NULL) {
		return false;
	}
	return this->conectar(he->h_addr_list[0]);
}

void Socket::desconectar() {
	this->conectado = false;
	this->enlazado = false;
	shutdown(fd, SHUT_RDWR);
}

bool Socket::enviar(const Mensaje& mensaje) {
	std::string s_datos = mensaje.serealizar();
	size_t parcial = 0;
	size_t enviado = 0;
	size_t total = s_datos.length();

	const char* datos = s_datos.c_str();

	while ((parcial < total) && conectado) {
		enviado = send(fd, datos + parcial, (total - parcial), 0);
		if (enviado <= 0) {
			conectado = false;
		} else {
			parcial += enviado;
		}
	}
	return conectado;
}

void Socket::recibir(Mensaje& mensaje) {
	bool finalizado = false;
	std::string s;
	s.clear();
	char* buffer =  new char[MAX_LENGTH_MESSAGE];

	while ((!finalizado) && conectado) {
		std::memset(buffer, 0, MAX_LENGTH_MESSAGE);
		int r = recv(fd, buffer, MAX_LENGTH_MESSAGE - 1, 0);
		// Si retorno 0, el socket remoto se desconecto
		if (r == 0) {
			this->conectado = false;
			break;
		}
		if (r < 0)  // error comunicacion
			break;

		s += buffer;
		if (s.at(s.length() - 1) == '\n')
			finalizado = true;
	}
	delete[] buffer;
	mensaje.deserealizar(s);
}
