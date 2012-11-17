// Header Include.
#include "ThreadCliente.h"

// C++ Library Includes.
#include <iostream>

// Common Project Includes.
#include "../../common/model/Escenario.h"

// Project Includes.
#include "MensajeServer.h"
#include "RespuestaServer.h"
#include "MensajeCliente.h"
#include "../modelo/NivelServer.h"

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
		case MC_VER_RECORDS:
			std::cout << "El cliente quiere ver la tabla de records." << std::endl;
			/* TODO enviar la tabla de records.
			 */
			r = new RespuestaServer(RS_TABLA_RECORDS, "Tabla de records.");
			this->socket->enviar(*r);
			break;
		case MC_CREAR_PARTIDA:
			std::cout << "El cliente quiere crear una partida." << std::endl;
			/* TODO enviar la lista de mundos
			 */
			r = new RespuestaServer(RS_LISTA_MUNDOS, "Lista de Mundos");
			this->socket->enviar(*r);
			break;
		case MC_VER_PARTIDAS:
			std::cout << "El cliente quiere ver partidas existentes." << std::endl;
			/* TODO enviar la lista de partidas
			 */
			r = new RespuestaServer(RS_LISTA_PARTIDAS, "Lista de partidas disponibles");
			this->socket->enviar(*r);
			break;
		case MC_UNIRSE_PARTIDA:
			std::cout << "El cliente quiere unirse a una partida." << std::endl;
			/* TODO intentar agregar el cliente a la partida y enviar resultado
			 */
			r = new RespuestaServer(RS_UNIRSE_PARTIDA_OK, "Hubo un error al unirse a una partida");
			this->socket->enviar(*r);
			this->correrJuego();
			break;
		case MC_DESCONECTAR:
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

void ThreadCliente::correrJuego() {
	Escenario escena;
	NivelServer nivel(&escena);
	nivel.cargarXML("../common/MiMundo-level1.xml");
	MensajeServer* msj;
	for(int i = 0; i < 200; i++) {
		msj = new MensajeServer(MS_EVENTO);
		nivel.tick(20);
		this->socket->enviar(*msj);
		std::cout << "tick " << i << std::endl;
		usleep(30000);
		delete msj;
	}

	msj = new MensajeServer(MS_FINALIZAR_PARTIDA);
	this->socket->enviar(*msj);

}
