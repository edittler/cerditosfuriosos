// Header Include.
#include "ThreadCliente.h"

// Project Includes.
#include "../common/communication/MensajeServer.h"
#include "../common/communication/MensajeCliente.h"

ThreadCliente::ThreadCliente() {
	// TODO Auto-generated constructor stub

}

ThreadCliente::ThreadCliente(Socket* socket) {
	this->socket = socket;
	// TODO Auto-generated destructor stub
}

ThreadCliente::~ThreadCliente() {
	// TODO Auto-generated destructor stub
}

void* ThreadCliente::run() {
	// FIXME implementacion prueba
	Mensaje* m =  new MensajeCliente();
	socket->recibir(*m);
	std::cout << "Mensajes recibido: " << m->serealizar() << std::endl;

	Mensaje* r = new MensajeServer();
	socket->enviar(*r);
	std::cout << "Mensajes enviado: " << r->serealizar() << std::endl;
	delete r;
	delete m;

	return NULL;
}
