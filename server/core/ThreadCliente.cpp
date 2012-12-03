// Header Include.
#include "ThreadCliente.h"

// C++ Library Includes.
#include <iostream>
#include <unistd.h>

// Common Project Includes.
#include "Escenario.h"
#include "MensajeServer.h"
#include "RespuestaServer.h"
#include "MensajeCliente.h"
#include "CFTools.h"
#include "Log.h"

// Server Project Includes.
#include "Server.h"
#include "ThreadPartida.h"
#include "../modelo/NivelServer.h"

ThreadCliente::ThreadCliente(Server& servidor, Socket* socket) :
		server(servidor) {
	this->conectado = true;
	this->socket = socket;
	this->idJugador = -1;
	this->threadPartida = NULL;
	this->tEnviar = new ThreadEnviar(*socket);
	this->tRecibir = new ThreadRecibir(*socket);
}

ThreadCliente::~ThreadCliente() {
	delete this->socket;
	delete this->tEnviar;
	delete this->tRecibir;
}

bool ThreadCliente::estaActivo() {
	return this->conectado;
}

void ThreadCliente::setPartida(ThreadPartida* partida) {
	this->threadPartida = partida;
}

void ThreadCliente::asignarJugador(unsigned int id) {
	this->idJugador = id;
}

unsigned int ThreadCliente::getJugadorAsignado() {
	return this->idJugador;
}

bool ThreadCliente::hayEventos() {
	return !this->colaEventos.estaVacia();
}

Evento ThreadCliente::desencolarEvento() {
	return this->colaEventos.obtenerFrente();
}

void ThreadCliente::enviar(Mensaje* m) {
	this->tEnviar->agregarMensaje(m);
}

Mensaje* ThreadCliente::recibir() {
	return this->tRecibir->getMensaje();
}

void ThreadCliente::finalizar() {
	this->conectado = false;
}

void* ThreadCliente::run() {
	this->tEnviar->start();
	this->tRecibir->start();

	while (conectado) {
		Mensaje* msj = tRecibir->getMensaje();
		if (msj ==  NULL)  // espero hasta recibir un mensaje
			continue;

		MensajeCliente* m = NULL;
		m = dynamic_cast<MensajeCliente*>(msj);

		// valido que el cliente no se haya desconectado
		if (!this->socket->estaConectado()) {
			this->conectado = false;

			// si esta dentro de una partida lo notifico.
			if (this->threadPartida != NULL) {
				this->threadPartida->abandonarPartida(this);
				this->threadPartida = NULL;
			}
			break;
		}
		// Obtengo el comando que envio el cliente
		ComandoCliente comandoCli = m->getComando();
		// Declaro el puntero a la respuesta a enviar.
		Mensaje* r = NULL;
		switch (comandoCli) {
		case MC_VER_RECORDS: {
			// Obtengo records de un mundo
			ListaRecords lista = server.getTablaRecords(m->getID());

			// serializo lista para agregar al formato usado para la comunicacion
			std::string mensaje;
			ListaRecords::iterator it;
			for (it = lista.begin(); it != lista.end(); ++it) {
				mensaje.append((*it).first); mensaje.push_back('%');
				mensaje.append(cft::intToString((*it).second)); mensaje.push_back('%');
			}

			r = new RespuestaServer(RS_TABLA_RECORDS, mensaje);
			this->socket->enviar(*r);
			break; }

		case MC_VER_MUNDOS: {
			std::string mensaje;
			std::list<std::string> listaMundos = server.getMundosDisponibles();

			// serializo lista para agregar al formato usado para la comunicacion
			std::list<std::string>::iterator it;
			for (it = listaMundos.begin(); it != listaMundos.end(); ++it) {
				mensaje.append(*it); mensaje.push_back('%');
			}

			// encolo mensaje para envio
			r = new RespuestaServer(RS_LISTA_MUNDOS, mensaje);
			tEnviar->agregarMensaje(r);
		break; }

		case MC_CREAR_PARTIDA: {
			// Se crea una partida con el nombre especificado y se registra
			// en el server.
			unsigned int id = Partida::generarId();
			Partida* partida = new Partida(id, m->getNombrePartida());

			// cargo XML correspondiente a la partida seleccionada
			std::string pathXML = server.getPathXMLMundo(m->getID());
			partida->setRutaMundo(pathXML);
			partida->cargarNiveles();

			partida->cargarSiguienteNivel();
			this->server.crearPartida(partida, this);
			break; }

		case MC_VER_PARTIDAS: {
			std::string mensaje;
			std::list<std::string> list = server.getPartidasDisponibles();

			// serializo lista para agregar al formato usado para la comunicacion
			std::list<std::string>::iterator it;
			for (it = list.begin(); it != list.end(); ++it) {
				mensaje.append(*it); mensaje.push_back('%');
			}

			// encolo mensaje para envio
			r = new RespuestaServer(RS_LISTA_PARTIDAS, mensaje);
			this->tEnviar->agregarMensaje(r);
			break; }

		case MC_UNIRSE_PARTIDA: {
			// obtengo id del mensaje y paso a unsigned int
			std::string respuesta = m->getID();
			int pos = respuesta.find_first_of(':');
			unsigned int id = cft::stringToUint(respuesta.substr(0, pos));

			// intentar agregar el cliente a la partida y enviar resultado
			if (this->server.unirseAPartida(id, this)) {  // se unio correctamnete
				// setea automaticamente el comando RS_UNIRSE_PARTIDA
				r = new RespuestaServer(this->idJugador);
				this->tEnviar->agregarMensaje(r);
			} else {  // no se unio correctamente
				r = new RespuestaServer(RS_UNIRSE_PARTIDA_ERROR);
				this->tEnviar->agregarMensaje(r);
			}

			break; }

		case MC_EVENTO: {
			Evento evento = m->getEvento();
			this->colaEventos.encolar(evento);
			break; }

		case MC_ABANDONAR_PARTIDA: {
			this->threadPartida->abandonarPartida(this);
			this->threadPartida = NULL;
			break; }

		case MC_DESCONECTAR: {
			if (threadPartida != NULL) {
				this->threadPartida->abandonarPartida(this);
				this->threadPartida = NULL;
			}
			this->socket->desconectar();
			this->conectado = false;
			break; }

		default: {
			break; }
		}

		delete m;
	}

	// finaliza threads enviar y recibir
	this->socket->desconectar();
	this->tEnviar->finalizar();
	this->tEnviar->join();
	this->tRecibir->finalizar();
	this->tRecibir->join();

	return NULL;
}
