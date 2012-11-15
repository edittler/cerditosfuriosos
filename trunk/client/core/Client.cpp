// Header Include.
#include "Client.h"

// C++ Library Includes.
#include <iostream>

// Project Includes.
#include "MensajeCliente.h"
#include "RespuestaServer.h"
#include "MensajeServer.h"
#include "ConstantesClientServer.h"

Client::Client() {
	this->serverIp = SERVER_IP_DEFAULT;
	this->socket = new Socket(PUERTO_DEFAULT);
	this->port = PUERTO_DEFAULT;
}

Client::Client(const char* ip, unsigned short int port) {
	this->serverIp = ip;
	this->socket = new Socket(port);
	this->port = port;
}

Client::~Client() {
	delete socket;
}

void Client::conectar() {
	this->socket->conectar(this->serverIp);
	/* TODO Si no se puede conectar, se debería mostrar un mensaje
	 * al usuario y retornar a la pantalla principal.
	 */
}

void Client::desconectar() {
	socket->desconectar();
}

bool Client::ejecutar() {
	// FIXME implementacion prueba
	Mensaje* r = new MensajeCliente(VerPartidas);
	socket->enviar(*r);
	std::cout << "Mensajes enviado: VerPartidas" << r->serealizar() << std::endl;

	RespuestaServer* m =  new RespuestaServer();
	socket->recibir(*m);
	std::cout << "Mensajes recibido: " << m->getDatos() << std::endl;

	delete r;
	r = new MensajeCliente(Desconectar);
	socket->enviar(*r);

	std::cout << "Mensajes enviado: Desconectar" << r->serealizar() << std::endl;

	delete r;
	delete m;

	return false;
}
