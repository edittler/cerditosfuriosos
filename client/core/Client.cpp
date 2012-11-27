// Header Include.
#include "Client.h"

// C++ Library Includes.
#include <iostream>

// Common Project Includes.
#include "../../communication/MensajeCliente.h"
#include "../../communication/RespuestaServer.h"
#include "../../communication/MensajeServer.h"

#include "../../common/model/Escenario.h"
#include "../../common/parser/XMLTypes.h"
#include "../../common/thread/Lock.h"

// Client Project Includes.
#include "ThreadRecibirCliente.h"
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
	this->_corriendoPartida = false;
	this->_partidaFinalizada = false;
	this->rutaNivelRecibido = RUTA_XML_NIVEL_TEMPORAL;
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
	// Envío el mensaje de desconectar
	Mensaje* mensaje = new MensajeCliente(MC_DESCONECTAR);
	socket->enviar(*mensaje);
	socket->desconectar();
	this->_partidaFinalizada = true;
	// Como el cliente puede estar corriendo en un thread a parte, hago un join.
	this->join();
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

std::string Client::getRutaNivel() const {
	return this->rutaNivelRecibido;
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

	/* Hago que la ventana muestre la lista de mundos
	 */
	ventana.modoCrearPartida(r.getDatos());
//	ventana.modoCrearPartida("El Mundo%");
}

void Client::botonMundoSeleccionado() {
	/* Envío un mensaje al servidor solicitando la creación de una nueva partida
	 * con el mundo seleccionado y el nombre elegido.
	 */
	std::string idMundo = ventana.panelCrearPartida->getMundoElegido();
	std::string nombrePartida = ventana.panelCrearPartida->getNombreElegido();
	MensajeCliente m(idMundo, nombrePartida);
	socket->enviar(m);
	std::cout << "Mensajes enviado:\n\tMundo Seleccionado: " << idMundo << std::endl;
	std::cout << "\tNombre Elegido: " << nombrePartida << std::endl;

	/* Como este cliente es el que está creando la partida, se autoasigna el
	 * idJugador con el valor 1.
	 */
	idJugador = 1;

	/* Ahora corro el thread del cliente para que éste comience a recibir
	 * mensajes del server y ejecutar la simulacion.
	 */
	this->start();
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

	ventana.modoUnirsePartida(r.getDatos());

}

void Client::botonPartidaSeleccionada() {
	std::string idPartida = ventana.panelUnirsePartida->selectorPartidas->
													getOpcionSeleccionada();
	/* Envío un mensaje que solicita unirse a la partida deseada.
	 */
	MensajeCliente m(idPartida);
	socket->enviar(m);

	/* Espero respuesta del server con la confirmación del pedido de unión a
	 * la partida
	 */
	RespuestaServer r;
	socket->recibir(r);
	RespuestaServidor comando = r.getTipoRespuesta();
	/* Si la respuesta es afirmativa, obtengo el ID del jugador y corro el
	 * thread que espera mensajes del server.
	 */
	if (comando == RS_UNIRSE_PARTIDA_OK) {
		idJugador = r.getIDJugador();
		this->start();
	} else {
		ventana.modoMultijugador();
	}
}

void Client::botonVerRecords() {
	MensajeCliente m(MC_VER_RECORDS);
	socket->enviar(m);
	std::cout << "Mensajes enviado: Ver Records" << std::endl;

	RespuestaServer r;
	socket->recibir(r);
	std::cout << "Mensajes recibido: " << r.getDatos() << std::endl;

	/* TODO Hacer que la vista muestre la tabla de records
	 */
}

void* Client::run() {
	// Creo un thread receptor
	ThreadRecibirCliente tReceptor(*socket);
	tReceptor.start();
	while (socket->estaConectado()) {
		Mensaje* m = tReceptor.getMensaje();
		if (m != NULL) {
			std::cout << m->serealizar() << std::endl;
			MensajeServer* ms = dynamic_cast<MensajeServer*>(m);
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
	/* Si finalizo el while, es porque se desconecto el socket, hago un join
	 * al thread receptor de mensajes
	 */
	tReceptor.join();
	return NULL;
}

void Client::guardarXML(std::string datosXMLNivel) const {
	XMLDocument doc;
	doc.Parse(datosXMLNivel.c_str(), 0, TIXML_ENCODING_UTF8);
	bool seGuardo = doc.SaveFile(this->rutaNivelRecibido);
	if (seGuardo) {
		std::cout << "se guardo el archivo.\n";
	}
}
