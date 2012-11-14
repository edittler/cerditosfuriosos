#include "Client.h"
#include "MensajeCliente.h"
#include "MensajeServer.h"
#include "ConstantesClientServer.h"

Client::Client() {
	this->serverIp = new std::string(SERVER_IP_DEFAULT);
	this->socket = new SocketCliente();
	this->port = PUERTO_DEFAULT;
}

Client::Client(const char* ip, unsigned short int port) {
	this->serverIp = new std::string(ip);
	this->socket = new SocketCliente();
	this->port = port;
}

Client::~Client() {
	delete socket;
	delete serverIp;
}

void Client::conectar() {
	this->socket->conectar(this->serverIp->c_str(), this->port);
}

void Client::desconectar() {
	socket->desconectar();
}

bool Client::ejecutar() {
	// FIXME implementacion prueba
	Mensaje* r = new MensajeCliente();
	socket->enviar(*r);
	std::cout << "Mensajes enviado: " << r->serealizar() << std::endl;

	Mensaje* m =  new MensajeServer();
	socket->recibir(*m);
	std::cout << "Mensajes recibido: " << m->serealizar() << std::endl;
	delete r;
	delete m;

	return false;
}
