// Header Include.
#include "ThreadCliente.h"

// C++ Library Includes.
#include <iostream>
#include <unistd.h>

// Common Project Includes.
#include "../../common/model/Escenario.h"
#include "MensajeServer.h"
#include "RespuestaServer.h"
#include "MensajeCliente.h"
#include "CFTools.h"

// Server Project Includes.
#include "Server.h"
#include "ThreadPartida.h"
#include "../modelo/NivelServer.h"

ThreadCliente::ThreadCliente(Server& servidor, Socket* socket) :
		server(servidor) {
	this->conectado = true;
	this->socket = socket;
	this->idJugador = -1;

	this->tEnviar = new ThreadEnviar(socket);
	this->tRecibir = new ThreadRecibir(socket);
}

ThreadCliente::~ThreadCliente() {
	this->socket->desconectar();
	delete this->socket;
	delete this->tEnviar;
	delete this->tRecibir;

//	while (!colaEventos.estaVacia()) {
//		Evento* e = colaEventos.obtenerFrente();
//		delete e;
//	}
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

//Evento ThreadCliente::popEvento() {
//	return this->colaEventos.obtenerFrente();
//}

void ThreadCliente::enviar(Mensaje* m) {
	this->tEnviar->agregarMensaje(m);
}

Mensaje* ThreadCliente::recibir() {
	return this->tRecibir->getMensaje();
}

void* ThreadCliente::run() {
	this->tEnviar->start();
	this->tRecibir->start();

	while (conectado) {
		// valido que el cliente no se haya desconectado
		if (!this->socket->estaConectado()) {
			this->conectado = false;

			// si esta dentro de una partida lo notifico.
			if (this->threadPartida != NULL) {
				this->threadPartida->abandonarPartida(this);
			}
			break;
		}

		MensajeCliente* m = NULL;
		while (m == NULL) {
			Mensaje* msj = tRecibir->getMensaje();
			m = dynamic_cast<MensajeCliente*>(msj);
		}

		// Obtengo el comando que envio el cliente
		ComandoCliente comandoCli = m->getComando();
		// Declaro el puntero a la respuesta a enviar.
		RespuestaServer* r = NULL;
		switch (comandoCli) {
		case MC_VER_RECORDS: {
			std::cout << "El cliente quiere ver la tabla de records." << std::endl;
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
			std::cout << "El cliente quiere ver la lista de mundos." << std::endl;
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
			std::cout << "El cliente quiere crear una partida." << std::endl;
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
			std::cout << "El cliente creo una partida satisfactoriamente." << std::endl;
			break; }

		case MC_VER_PARTIDAS: {
			std::cout << "El cliente quiere ver partidas existentes." << std::endl;
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
			std::cout << "El cliente quiere unirse a una partida." << std::endl;
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

			this->correrJuego();
			break; }

		case MC_EVENTO: {
			std::cout << "El cliente comunico un evento." << std::endl;

			// TODO los eventos deberian ingresarse a una cola dentro del ThreadCliente y el
			// ThreadPartida deberia leerlo desde ahi
			Evento evento = m->getEvento();
//			this->colaEventos.encolar(evento);

			break; }

		case MC_ABANDONAR_PARTIDA: {
			std::cout << "El cliente quiere abandonar la partida." << std::endl;
			this->threadPartida->abandonarPartida(this);
			break; }

		case MC_DESCONECTAR: {
			std::cout << "El cliente se va a desconectar." << std::endl;
			this->threadPartida->abandonarPartida(this);
			this->conectado = false;
			break; }

		default: {
			std::cout << "El cliente envió un comando inválido" << std::endl;
			break; }
		}
		if (r != NULL)
			delete r;

		delete m;
	}

	// FIXME Una vez terminado el loop el cliente se desconecto de la aplicacion
	// deberia eliminarse de la lista de ClientesConectados del server.

	return NULL;
}

void ThreadCliente::correrJuego() {
	NivelServer nivel;
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
			this->tEnviar->agregarMensaje(msj);
		}
		Evento tick(E_CORRER_TICK);
		msj = new MensajeServer(tick);
		nivel.tick(20);
		this->tEnviar->agregarMensaje(msj);
		std::cout << "tick " << i << std::endl;
		usleep(30000);
	}

	msj = new MensajeServer(MS_FINALIZAR_PARTIDA);
	this->socket->enviar(*msj);
	delete msj;
}
