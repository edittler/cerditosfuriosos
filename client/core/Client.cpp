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
	this->port = PUERTO_DEFAULT;
	this->socket = new Socket(this->port);
}

Client::Client(std::string ip, Puerto port) {
	this->serverIp = ip;
	this->socket = new Socket(port);
	this->port = port;
}

Client::~Client() {
	// Si el socket se encuentra conectado, lo desconecto.
	if (socket->estaConectado())
		socket->desconectar();
	delete socket;
}

bool Client::conectar() {
	bool seConecto = this->socket->conectar(this->serverIp);
	return seConecto;
}

void Client::desconectar() {
	socket->desconectar();
	this->_partidaFinalizada = true;
}

//void Client::ejecutar() {
	/* En modo multijugador se debe crear una ventana con 3 opciones:
	 * CREAR PARTIDA, UNIRSE A PARTIDA, VER RECORDS, REGRESAR AL MENU PRINCIPAL.
	 * Regresar al menú principal, implica desconectarse del servidor.
	 */

	/* Inicializo el comando que se establecerá segun los botones que pulse
	 * el cliente.
	 */
//	ComandoCliente comando = MC_INDEFINIDO;

	/* Mientras el comando sea distinto de DESCONECTAR, repito la secuencia del
	 * modo multijugador.
	 */
//	while (comando != MC_DESCONECTAR) {
		/* Dibujo la pantalla de selección de opciones y espero la selección
		 */
		// FIXME Provisoriamente, establezco que voy a unirme a la partida.
//		comando = MC_UNIRSE_PARTIDA;

/*		switch (comando) {
		case MC_CREAR_PARTIDA:
			this->crearPartida();
			break;
		case MC_UNIRSE_PARTIDA:
			this->unirsePartida();
			// FIXME Como no hay menues, provisoriamente establezco desconectar
			comando = MC_DESCONECTAR;
			break;
		case MC_VER_RECORDS:
			this->verRecords();
			break;
		case MC_DESCONECTAR:
			comando = MC_DESCONECTAR;
			break;
		default:
			// No realizo nada
			break;
		}
	}
}*/

Socket& Client::getSocket() const {
	return (*socket);
}

unsigned int Client::getIDJugdor() const {
	return this->idJugador;
}

ColaProtegida<Evento>& Client::getColaEvento() {
	return this->colaEventos;
}

bool Client::conectado() const {
	return this->socket->estaConectado();
}

bool Client::corriendoPartida() {
	if (_corriendoPartida && !_partidaFinalizada)
		return true;
	else
		return false;
}

bool Client::partidaPausada() {
	return !_corriendoPartida;
}

bool Client::partidaFinalizada() {
	return _partidaFinalizada;
}

void Client::botonCrearPartida() {
	/* Envío un mensaje al servidor solicitando la lista de mundos para poder
	 * crear una partida.
	 */
	MensajeCliente m(MC_VER_MUNDOS);
	socket->enviar(m);
	std::cout << "Mensajes enviado: Ver Mundos" << std::endl;

	// Espero respuesta del servidor con la lista de mundos.
	RespuestaServer r;
	socket->recibir(r);
	std::cout << "Mensajes recibido: " << r.getDatos() << std::endl;

	/* TODO debo decodificar la lista de mundos, crear una pantalla donde
	 * cada mundo disponible tenga un botón y luego de la seleccion debo enviar
	 * nuevamente el mensaje CREAR_PARTIDA especificando el mundo seleccionado.
	 */

}

void Client::botonUnirsePartida() {
		/* Envío un mensaje que solicita la lista de partidas a para poder
		 * unirse.
		 */
		MensajeCliente m(MC_VER_PARTIDAS);
		socket->enviar(m);
		std::cout << "Mensajes enviado: Ver Partidas" << std::endl;

		// Espero una respuesta del server con una lista de partidas disponibles.
		RespuestaServer r;
		socket->recibir(r);
		std::cout << "Mensajes recibido: " << r.getDatos() << std::endl;
		 /* Decodifico la lista de partidas. Se debe crear una pantalla donde
		 * cada partida tiene asociada un botón y además se encuenta el botón
		 * de regresar a la pantalla de menu multijugador.
		 * Cuando el usuario selecciona una partida, envia nuevamente al server
		 * UNIRSE_PARTIDA adjuntando el ID de la partida.
		 * Si el usuario selecciona regresar, establezco como true el booleano.
		 */
		// TODO implementar del lado der servidor esta lógica.
		/* FIXME provisoriamente ejecuto correrJuego que contiene un demo.
		 * y establezco como true regresar.
		 */
}

void Client::botonVerRecords() {
	MensajeCliente m(MC_VER_RECORDS);
	socket->enviar(m);
	std::cout << "Mensajes enviado: Ver Records" << std::endl;

	RespuestaServer r;
	socket->recibir(r);
	std::cout << "Mensajes recibido: " << r.getDatos() << std::endl;

	/* TODO debo decodificar la tabla de records, crear una pantalla donde
	 * se muestre dicha tabla y mostrar un botón para regresar a la pantalla
	 * de menu multijugador.
	 */
}

void* Client::run() {
	return NULL;
}

/*
void Client::correrJuego() {
	Escenario escenario;
	NivelProxy nivel(1);
	nivel.cargarXML("../common/MiMundo-level1.xml");

	MensajeServer* msjServer;
	int i = 0;
	while (!nivel.finalizoPartida()) {
		msjServer = new MensajeServer();
		this->socket->recibir(*msjServer);
		if (msjServer->getComando() == MS_EVENTO) {
			nivel.procesarEvento(msjServer->getEvento());
		}
		if (msjServer->getComando() == MS_FINALIZAR_PARTIDA) {
			std::cout << "Fin nivel " << i++ << std::endl;
			break;
		}
	}

	MensajeCliente m(MC_DESCONECTAR);
	socket->enviar(m);
	std::cout << "Mensajes enviado: Desconectar" << std::endl;
} */
