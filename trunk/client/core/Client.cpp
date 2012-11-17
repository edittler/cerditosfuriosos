// Header Include.
#include "Client.h"

// C++ Library Includes.
#include <iostream>

// Common Project Includes.
#include "../../common/model/Escenario.h"
#include "MensajeCliente.h"
#include "RespuestaServer.h"
#include "MensajeServer.h"
#include "ConstantesClientServer.h"

// Client Project Includes.
#include "../modelo/NivelProxy.h"

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
	Mensaje* r = new MensajeCliente(MC_UNIRSE_PARTIDA);
	socket->enviar(*r);
	std::cout << "Mensajes enviado: UnirsePartidas" << std::endl;

	RespuestaServer* m =  new RespuestaServer();
	socket->recibir(*m);
	std::cout << "Mensajes recibido: " << m->getDatos() << std::endl;
	delete r;

	// TODO Cargo el XML del nivel que debería recibir del server
	/* TODO Se podria hacer que el Nivel base ya contenga un escenario y que
	 * lo cree al hidratarse.
	 */
	Escenario escenario;
	Nivel* nivel = new NivelProxy(&escenario);
	nivel->cargarXML("../common/MiMundo-level1.xml");

	bool finalizo = false;

	MensajeServer* msjServer;
	int i = 0;
	while (!finalizo) {
		std::cout << "Loop: ";
		msjServer = new MensajeServer();
		this->socket->recibir(*msjServer);
		if (msjServer->getComando() == MS_EVENTO) {
			nivel->tick(20);
			std::cout << "tick " << i++ << std::endl;
		}
		if (msjServer->getComando() == MS_FINALIZAR_PARTIDA) {
			finalizo = true;
			std::cout << "Fin nivel " << i++ << std::endl;
		}
	}

	delete nivel;

	r = new MensajeCliente(MC_DESCONECTAR);
	socket->enviar(*r);
	std::cout << "Mensajes enviado: Desconectar" << std::endl;

	delete r;
	delete m;

	return false;
}

