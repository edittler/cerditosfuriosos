// Header Include.
#include "ThreadCliente.h"

// C++ Library Includes.
#include <iostream>

// Common Project Includes.
#include "../../common/model/Escenario.h"
#include "MensajeServer.h"
#include "RespuestaServer.h"
#include "MensajeCliente.h"

// Server Project Includes.
#include "Server.h"
#include "../modelo/NivelServer.h"

ThreadCliente::ThreadCliente(Server& servidor, Socket* socket) :
		server(servidor) {
	this->conectado = true;
	this->socket = socket;
}

ThreadCliente::~ThreadCliente() {
	delete this->socket;
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
		// Si el contador es multipo de 20, lanzo un pajaro
		if ((i%20) == 0) {
			// Lanzar pajaro
			Punto2D p(2.45, 3.45);
			Velocidad2D v(3, 0.05);
			nivel.lanzarPajaroVerde(p, v);
			Evento evPajVerde(T_PAJARO_VERDE, p, v);
			std::cout << "lanzo pajaro verde" << std::endl;
			std::cout << "Posicion\tx= " << p.x << "\ty = " << p.y << std::endl;
			std::cout << "Velocidad\tx= " << v.x << "\ty = " << v.y << std::endl;
			msj = new MensajeServer(evPajVerde);
			this->socket->enviar(*msj);
			delete msj;
		}
		Evento tick(E_CORRER_TICK);
		msj = new MensajeServer(tick);
		nivel.tick(20);
		this->socket->enviar(*msj);
		std::cout << "tick " << i << std::endl;
		usleep(30000);
		delete msj;
	}

	msj = new MensajeServer(MS_FINALIZAR_PARTIDA);
	this->socket->enviar(*msj);
	delete msj;
}
