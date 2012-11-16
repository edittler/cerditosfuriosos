// Header Include.
#include "ThreadCliente.h"

// C++ Library Includes.
#include <iostream>

// Project Includes.
#include "MensajeServer.h"
#include "RespuestaServer.h"
#include "MensajeCliente.h"

ThreadCliente::ThreadCliente() { }

ThreadCliente::ThreadCliente(Socket* socket) {
	this->conectado = true;
	this->socket = socket;
}

ThreadCliente::~ThreadCliente() {
	// TODO Auto-generated destructor stub
}

void* ThreadCliente::run() {
	while (conectado) {
		MensajeCliente m;
		socket->recibir(m);
		// Obtengo el comando que envio el cliente
		ComandoCliente comandoCli = m.getComando();
		// Declaro el puntero a la respuesta a enviar.
		RespuestaServer* r = NULL;
		switch (comandoCli) {
		case VerRecords:
			std::cout << "El cliente quiere ver la tabla de records." << std::endl;
			/* TODO enviar la tabla de records.
			 */
			r = new RespuestaServer(TablaRecords, "Tabla de records.");
			this->socket->enviar(*r);
			break;
		case CrearPartida:
			std::cout << "El cliente quiere crear una partida." << std::endl;
			/* TODO enviar la lista de mundos
			 */
			r = new RespuestaServer(ListaMundos, "Lista de Mundos");
			this->socket->enviar(*r);
			break;
		case VerPartidas:
			std::cout << "El cliente quiere ver partidas existentes." << std::endl;
			/* TODO enviar la lista de partidas
			 */
			r = new RespuestaServer(ListaPartidas, "Lista de partidas disponibles");
			this->socket->enviar(*r);
			break;
		case UnirsePartida:
			std::cout << "El cliente quiere unirse a una partida." << std::endl;
			/* TODO intentar agregar el cliente a la partida y enviar resultado
			 */
			r = new RespuestaServer(ErrorUnirsePartida, "Hubo un error al unirse a una partida");
			this->socket->enviar(*r);
			break;
		case Desconectar:
			std::cout << "El cliente se va a desconectar." << std::endl;
			this->conectado = false;
			break;
		default:
			std::cout << "El cliente envió un comando inválido" << std::endl;
			break;
		}
		if (r != NULL)
			delete r;
	}

	return NULL;
}
