#include "Server.h"

Server::Server() {
	encendido = false;
	port = PUERTO_DEFAULT;

	socket = new SocketServer();
	clientesEnEspera = new ClientesEnEspera();
	// TODO Auto-generated constructor stub

}

Server::Server(unsigned short int port) {
	encendido = false;
	this->port = port;

	socket = new SocketServer();
	clientesEnEspera = new ClientesEnEspera();
	// TODO Auto-generated constructor stub
}

Server::~Server() {
	delete clientesEnEspera;
	delete socket;
	// TODO Auto-generated destructor stub
}

void Server::prender() {
	// TODO completar implementacion
	encendido = true;

	// inicializa Server Socket.
	socket->enlazar(this->port);
	socket->escuchar(MAX_CONEXION_ESPERA);
}

void Server::apagar() {
	// TODO completar implementacion
	encendido = false;

	// finaliza Server Socket
	socket->desconectar();
}

void Server::registrarCliente(ThreadCliente* cliente) {
	clientesEnEspera->push_back(cliente);
	cliente->start();
}
