// Header Include.
#include "Client.h"

// C++ Library Includes.
#include <iostream>

// Common Project Includes.
#include "../../communication/MensajeCliente.h"
#include "../../communication/RespuestaServer.h"
#include "../../communication/MensajeServer.h"
#include "../../communication/ThreadRecibir.h"
#include "../../common/model/Escenario.h"
#include "../../common/parser/XMLTypes.h"
#include "../../common/thread/Lock.h"

// Client Project Includes.
#include "../modelo/NivelProxy.h"
#include "ConstantesClientServer.h"

// Constantes del Client
#define RUTA_XML_NIVEL_TEMPORAL "xmlniveltemporal.xml"

Client::Client(VentanaPrincipal& ventana) : ventana(ventana) {
	this->serverIp = SERVER_IP_DEFAULT;
	this->port = PUERTO_DEFAULT;
	this->socket = new Socket(this->port);
	this->_corriendoPartida = false;
	this->_partidaFinalizada = false;
	this->rutaNivelRecibido = RUTA_XML_NIVEL_TEMPORAL;
}

Client::Client(VentanaPrincipal& ventana, std::string ip, Puerto port) :
		ventana(ventana) {
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
	Lock(this->mBoolsPartida);
	if (_corriendoPartida && !_partidaFinalizada)
		return true;
	else
		return false;
}

bool Client::partidaPausada() {
	Lock(this->mBoolsPartida);
	return !_corriendoPartida;
}

bool Client::partidaFinalizada() {
	Lock(this->mBoolsPartida);
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
	// Creo un thread receptor
	ThreadRecibir tReceptor(*socket);
	tReceptor.start();
	while (socket->estaConectado()) {
		Mensaje* m = tReceptor.getMensaje();
		if (m != NULL) {
			MensajeServer* ms = static_cast<MensajeServer*>(m);
			// Si la conversión resulto existosa, interpreto el mensaje
			if (ms != NULL) {
				ComandoServer comando = ms->getComando();
				switch (comando) {
				case MS_CARGAR_NIVEL:
					// Almaceno el xml que contiene el xml
					this->guardarXML(ms->getXMLNivel());
					// Establezco que la partida está corriendo
					Lock(this->mBoolsPartida);
					this->_corriendoPartida = true;
					break;
				case MS_EVENTO:
					colaEventos.encolar(ms->getEvento());
					Lock(this->mBoolsPartida);
					// Si la partida estaba pausada, la marco como corriendo
					if (this->_corriendoPartida == false)
						this->_corriendoPartida = true;
					break;
				case MS_PAUSAR_PARTIDA:
					Lock(this->mBoolsPartida);
					this->_corriendoPartida = false;
					break;
				case MS_FINALIZAR_PARTIDA:
					Lock(this->mBoolsPartida);
					this->_partidaFinalizada = true;
					break;
				default:
					break;
				}  // Fin switch
			}  // Fin if (ms != NULL)
		}  // Fin if (m != NULL)
	}  // Fin while socket conectado.
	return NULL;
}

void Client::guardarXML(std::string datosXMLNivel) const {
	XMLDocument doc;
	doc.Parse(datosXMLNivel.c_str(), 0, TIXML_ENCODING_UTF8);
	doc.SaveFile(this->rutaNivelRecibido);
}
