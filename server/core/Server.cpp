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

	this->join();
}

void Server::prender() {
	// Establezco que el servidor está encendido.
	encendido = true;
	// Habilito el socket para conectarse y escuchar conexiones.
	socket->enlazar();
	socket->escucharConexiones(MAX_CONEXION_ESPERA);
	// Comienzo el thread para aceptar clientes
	this->start();
//	this->listener = new ThreadListener(this);
//	this->listener->start();
}

void Server::apagar() {
	// Establezco que el servidor está apagado
	encendido = false;
	// Desconecto el socket del servidor
	socket->desconectar();
	// Finalizo el listener de forma ordenada
//	this->listener->join();
}

void Server::crearPartida() {
	unsigned int id = 0;  // FIXME generar id
	ThreadPartida* partida = new ThreadPartida(new Partida(id));

	// TODO Agregar Cliente a la partida.
	std::pair<unsigned int, ThreadPartida*> p(id, partida);
	this->partidasDisponibles.insert(p);

	partida->start();
}

void* Server::run() {
	while (this->encendido) {
		Socket* socket = this->socket->aceptarConexion();

		if (socket == NULL)
			continue;

		ThreadCliente* cliente = new ThreadCliente(socket);
		this->clientesConectados.push_back(cliente);
		cliente->start();
	}
	return NULL;
}
