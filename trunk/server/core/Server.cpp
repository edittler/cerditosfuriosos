#include "Server.h"

Server::Server() {
	encendido = false;

	socket = new Socket(PUERTO_DEFAULT);
	// TODO Auto-generated constructor stub

}

Server::Server(unsigned short int port) {
	encendido = false;

	socket = new Socket(port);
	// TODO Auto-generated constructor stub
}

Server::~Server() {
	ClientesConectados::iterator itCl;
	for (itCl = clientesConectados.begin(); itCl != clientesConectados.end(); ++itCl) {
		delete (*itCl);
	}

	PartidasDisponibles::iterator itPa;
	for (itPa = partidasDisponibles.begin(); itPa != partidasDisponibles.end(); ++ itPa) {
		delete itPa->second;
	}

	delete socket;
	// TODO Auto-generated destructor stub
}

void Server::prender() {
	// TODO completar implementacion
	encendido = true;

	// inicializa Server Socket.
	socket->enlazar();
	socket->escucharConexiones(MAX_CONEXION_ESPERA);
}

void Server::apagar() {
	// TODO completar implementacion
	encendido = false;

	// finaliza Server Socket
	socket->desconectar();
}

void Server::crearPartida() {
	unsigned int id = 0;  // FIXME generar id
	ThreadPartida* t = new ThreadPartida(new Partida(id));

	// TODO Agregar Cliente a la partida.
	std::pair<unsigned int, ThreadPartida*> p(id, t);
	this->partidasDisponibles.insert(p);

	t->start();
}

void Server::registrarCliente(ThreadCliente* cliente) {
	clientesConectados.push_back(cliente);
	cliente->start();
}
