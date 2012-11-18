// Header Include.
#include "Server.h"

Server::Server() {
	this->encendido = false;
	this->socket = new Socket(PUERTO_DEFAULT);
}

Server::Server(Puerto port) {
	this->encendido = false;
	this->socket = new Socket(port);
}

Server::~Server() {
	// Si el servidor aún está encendido, lo apago
	if (this->encendido)
		this->apagar();

	ClientesConectados::iterator itCl;
	for (itCl = clientesConectados.begin(); itCl != clientesConectados.end(); ++itCl) {
		(*itCl)->join();
		delete (*itCl);
	}

	PartidasDisponibles::iterator itPa;
	for (itPa = partidasDisponibles.begin(); itPa != partidasDisponibles.end(); ++ itPa) {
		delete itPa->second;
	}

	delete socket;
}

void Server::prender() {
	// Establezco que el servidor está encendido.
	encendido = true;
	// Habilito el socket para conectarse y escuchar conexiones.
	socket->enlazar();
	socket->escucharConexiones(MAX_CONEXION_ESPERA);
	// Comienzo el thread para aceptar clientes
	this->start();
}

void Server::apagar() {
	// Establezco que el servidor está apagado
	encendido = false;
	// Desconecto el socket del servidor
	socket->desconectar();
	this->join();
}

void Server::crearPartida(Partida* partida, ThreadCliente* cliente) {
	unsigned int id = 0;  // FIXME generar id
	ThreadPartida* tPartida = new ThreadPartida(partida, cliente);

	std::pair<unsigned int, ThreadPartida*> p(id, tPartida);
	this->partidasDisponibles.insert(p);

	tPartida->start();
}

void* Server::run() {
	while (this->encendido) {
		Socket* socket = this->socket->aceptarConexion();

		if (socket == NULL)
			continue;

		ThreadCliente* cliente = new ThreadCliente(*this, socket);
		this->clientesConectados.push_back(cliente);
		cliente->start();
	}
	return NULL;
}
