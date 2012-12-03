// Header Include.
#include "Client.h"

// Common Project Includes.
#include "../../communication/MensajeCliente.h"
#include "../../communication/RespuestaServer.h"
#include "../../communication/MensajeServer.h"
#include "../../common/model/Escenario.h"
#include "../../common/parser/XMLTypes.h"
#include "../../common/thread/Lock.h"
#include "../../common/tools/CFTools.h"
#include "../../common/tools/ArchivoConfiguracion.h"

// Client Project Includes.
#include "ThreadRecibirCliente.h"
#include "../modelo/NivelProxy.h"
#include "ConstantesClientServer.h"

// Constantes de configuracion
#define RUTA_CONFIGURACION "client.config"
#define ATRIBUTO_DIRECCION "direccion"
#define ATRIBUTO_PUERTO "puerto"

// Constante de la ruta de archivo xml temporal
#define RUTA_XML_NIVEL_TEMPORAL "xmlniveltemporal.xml"

Client::Client(VentanaPrincipal& ventana) :
		ventana(ventana) {
	this->socket = NULL;
	this->_corriendoPartida = false;
	this->_partidaFinalizada = false;
	this->rutaNivelRecibido = RUTA_XML_NIVEL_TEMPORAL;
	this->cargarConfiguracion();
}

Client::~Client() {
	// Si el socket se encuentra conectado, lo desconecto.
	if (socket != NULL) {
		socket->desconectar();
		delete socket;
	}
}

bool Client::conectar() {
	Lock(this->mSocket);
	if (socket != NULL) {
		socket->desconectar();
		delete socket;
	}
	this->cargarConfiguracion();
	this->socket = new Socket(this->port);
	bool seConecto = this->socket->conectar(this->serverIp);
	// Establezco los flags en valores correspondientes
	Lock(this->mBoolsPartida);
	this->_corriendoPartida = false;
	this->_partidaFinalizada = false;
	// Conecto el socket
	return seConecto;
}

void Client::desconectar() {
	Lock(this->mSocket);
	if (socket == NULL)
		return;
	// Envío el mensaje de desconectar
	Mensaje* mensaje = new MensajeCliente(MC_DESCONECTAR);
	socket->enviar(*mensaje);
	// Desconecto el socket
	socket->desconectar();
	// Establezco los flags en valores correspondientes
	Lock(this->mBoolsPartida);
	this->_corriendoPartida = false;
	this->_partidaFinalizada = true; // Para finalizar el thread.
	// Como el cliente puede estar corriendo en un thread a parte, hago un join.
	this->join();
	// Una vez finalizado el thread, elimino el socket
	delete socket;
	socket = NULL;
}

Socket& Client::getSocket() {
	Lock(this->mSocket);
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

bool Client::conectado() {
	Lock(this->mSocket);
	if (socket != NULL)
		return this->socket->estaConectado();
	else
		return false;
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

void Client::botonConfiguracion() {
	this->ventana.modoConfiguracion(this->serverIp, this->port);
}

void Client::botonGuardarConfiguracion() {
	Lock(this->mSocket);
	// Si el socket está conectado, lo desconecto y elimino.
	if (socket != NULL) {
		socket->desconectar();
		delete socket;
		socket = NULL;
	}
	// Cargo los nuevos datos cargados por el usuario.
	this->serverIp = this->ventana.panelConfiguracion->getDireccion();
	this->port = this->ventana.panelConfiguracion->getPuerto();
	// Guardo los datos en el archivo de configuracion
	ArchivoConfiguracion archivo;
	archivo.setAtributo(ATRIBUTO_DIRECCION, this->serverIp);
	archivo.setAtributo(ATRIBUTO_PUERTO, cft::uintToString(this->port));
	archivo.guardar(RUTA_CONFIGURACION);
	// Regreso al menú principal
	ventana.volverAMenuPrincipal();
}

void Client::botonCrearPartida() {
	Lock(this->mSocket);
	if (socket == NULL) {
		ventana.volverAMenuPrincipal();
		ventana.mostrarDialogo(
				"No se ha establecido una conexión con el servidor");
		return;
	}
	/* Envío un mensaje al servidor solicitando la lista de mundos para poder
	 * crear una partida.
	 */
	MensajeCliente m(MC_VER_MUNDOS);
	socket->enviar(m);

	// Espero respuesta del servidor con la lista de mundos.
	RespuestaServer r;
	socket->recibir(r);

	/* Verifico si el server mandó un tipo de respuesta RS_LISTA_MUNDOS.
	 * Si mandó otro tipo de respuesta, muestro un error y vuelvo al panel
	 * multijugador.
	 */
	if (r.getTipoRespuesta() != RS_LISTA_MUNDOS) {
		ventana.mostrarDialogo("Se recibió información inválida.");
		return;
	}
	/* Si el socket sigue conectado, muestro la lista de mundos.
	 * Sino, regreso al panel principal e indico que se perdió la conexion con
	 * el server.
	 */
	if (socket->estaConectado()) {
		ventana.modoCrearPartida(r.getDatos());
	} else {
		ventana.volverAMenuPrincipal();
		ventana.mostrarDialogo("Se perdió la conexión con el servidor");
	}

}

void Client::botonMundoSeleccionado() {
	Lock(this->mSocket);
	if (socket == NULL) {
		ventana.volverAMenuPrincipal();
		ventana.mostrarDialogo(
				"No se ha establecido una conexión con el servidor");
		return;
	}
	/* Envío un mensaje al servidor solicitando la creación de una nueva partida
	 * con el mundo seleccionado y el nombre elegido.
	 */
	std::string idMundo = ventana.panelCrearPartida->getMundoElegido();
	std::string nombrePartida = ventana.panelCrearPartida->getNombreElegido();
	MensajeCliente m(idMundo, nombrePartida);
	socket->enviar(m);

	// Seteo los booleanos en valores correspondientes
	this->_corriendoPartida = false;
	this->_partidaFinalizada = false;

	/* Como este cliente es el que está creando la partida, se autoasigna el
	 * idJugador con el valor 1.
	 */
	idJugador = 1;

	if (socket->estaConectado()) {
		/* Ahora corro el thread del cliente para que éste comience a recibir
		 * mensajes del server y ejecutar la simulacion.
		 */
		ventana.modoEsperandoJugadores();
		this->start();
	} else {
		ventana.volverAMenuPrincipal();
		ventana.mostrarDialogo("Se perdió la conexión con el servidor");
	}
}

void Client::botonUnirsePartida() {
	Lock(this->mSocket);
	if (socket == NULL) {
		ventana.volverAMenuPrincipal();
		ventana.mostrarDialogo(
				"No se ha establecido una conexión con el servidor");
		return;
	}
	/* Envío un mensaje que solicita la lista de partidas a para poder
	 * unirse.
	 */
	MensajeCliente m(MC_VER_PARTIDAS);
	socket->enviar(m);

	// Espero una respuesta del server con una lista de partidas disponibles.
	RespuestaServer r;
	socket->recibir(r);

	/* Verifico si el server mandó un tipo de respuesta RS_LISTA_PARTIDAS.
	 * Si mandó otro tipo de respuesta, muestro un error y vuelvo al panel
	 * multijugador.
	 */
	if (r.getTipoRespuesta() != RS_LISTA_PARTIDAS) {
		ventana.mostrarDialogo("Se recibió información inválida.");
		return;
	}
	/* Si el socket sigue conectado, muestro la lista de partidas.
	 * Sino, regreso al panel principal e indico que se perdió la conexion con
	 * el server.
	 */
	if (socket->estaConectado()) {
		ventana.modoUnirsePartida(r.getDatos());
	} else {
		ventana.volverAMenuPrincipal();
		ventana.mostrarDialogo("Se perdió la conexión con el servidor");
	}
}

void Client::botonPartidaSeleccionada() {
	Lock(this->mSocket);
	if (socket == NULL) {
		ventana.volverAMenuPrincipal();
		ventana.mostrarDialogo(
				"No se ha establecido una conexión con el servidor");
		return;
	}
	if (ventana.panelUnirsePartida->selectorPartidas->hayOpcionesSeleccionables()) {
		std::string idPartida =
				ventana.panelUnirsePartida->selectorPartidas->getOpcionSeleccionada();
		/* Envío un mensaje que solicita unirse a la partida deseada.
		 */
		MensajeCliente m(idPartida);
		socket->enviar(m);

		/* Espero respuesta del server con la confirmación del pedido de unión a
		 * la partida
		 */
		RespuestaServer r;
		socket->recibir(r);

		if (socket->estaConectado()) {
			RespuestaServidor comando = r.getTipoRespuesta();
			/* Si la respuesta es afirmativa, obtengo el ID del jugador y corro el
			 * thread que espera mensajes del server.
			 */
			if (comando == RS_UNIRSE_PARTIDA_OK) {
				idJugador = r.getIDJugador();
				ventana.modoEsperandoJugadores();
				// Seteo los booleanos en valores correspondientes
				this->_corriendoPartida = false;
				this->_partidaFinalizada = false;
				this->start();
			} else {
				ventana.mostrarDialogo("No fue posible unirse a la partida.");
				ventana.modoMultijugador();
			}
		} else {
			ventana.volverAMenuPrincipal();
			ventana.mostrarDialogo("Se perdió la conexión con el servidor");
		}
	}
}

void Client::botonVerRecords() {
	Lock(this->mSocket);
	if (socket == NULL) {
		ventana.volverAMenuPrincipal();
		ventana.mostrarDialogo(
				"No se ha establecido una conexión con el servidor");
		return;
	}
	MensajeCliente m(MC_VER_RECORDS);
	socket->enviar(m);

	RespuestaServer r;
	socket->recibir(r);

	/* Verifico si el server mandó un tipo de respuesta RS_TABLA_RECORDS.
	 * Si mandó otro tipo de respuesta, muestro un error y vuelvo al panel
	 * multijugador.
	 */
	if (r.getTipoRespuesta() != RS_TABLA_RECORDS) {
		ventana.mostrarDialogo("Se recibió información inválida.");
		return;
	}
	/* Si el socket sigue conectado, muestro la tabla de records.
	 * Sino, regreso al panel principal e indico que se perdió la conexion con
	 * el server.
	 */
	if (socket->estaConectado()) {
		/* TODO Hacer que la vista muestre la tabla de records
		 */
	} else {
		ventana.volverAMenuPrincipal();
		ventana.mostrarDialogo("Se perdió la conexión con el servidor");
	}
}

void Client::botonAbandonarPartida() {
	Lock(this->mSocket);
	if (socket == NULL) {
		ventana.volverAMenuPrincipal();
		ventana.mostrarDialogo(
				"No se ha establecido una conexión con el servidor");
		return;
	}
	// Establezco los booleanos en los flags correspondientes
	this->_corriendoPartida = false;
	this->_partidaFinalizada = true; // Para finalizar el thread
	MensajeCliente m(MC_ABANDONAR_PARTIDA);
	socket->enviar(m);
	/* Envío otro mensaje que requiera respuesta para desbloquear el thread
	 * receptor
	 */
	m.set(MC_VER_MUNDOS);
	socket->enviar(m);

	if (socket->estaConectado()) {
		ventana.modoMultijugador();
	} else {
		ventana.volverAMenuPrincipal();
		ventana.mostrarDialogo("Se perdió la conexión con el servidor");
	}
}

void* Client::run() {
	// Creo un thread receptor
	ThreadRecibirCliente tReceptor(*socket);
	tReceptor.start();
	while (!_partidaFinalizada) {
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
					if (!_corriendoPartida)
						this->_corriendoPartida = true;
					break;
				case MS_PAUSAR_PARTIDA:
					Lock(this->mBoolsPartida);
					this->_corriendoPartida = false;
					break;
				case MS_FINALIZAR_PARTIDA:
					Lock(this->mBoolsPartida);
					this->_partidaFinalizada = true;
					this->_corriendoPartida = false;
					break;
				default:
					break;
				} // Fin switch
			} // Fin if (ms != NULL)
		} // Fin if (m != NULL)
	} // Fin while socket conectado.
	/* Si finalizo el while, es porque se desconecto el socket, hago un join
	 * al thread receptor de mensajes
	 */
	tReceptor.finalizar();
	tReceptor.join();
	return NULL;
}

void Client::cargarConfiguracion() {
	ArchivoConfiguracion archivo;
	bool seCargo = archivo.cargar(RUTA_CONFIGURACION);
	/* Si el archivo no se cargó, creo uno nuevo y guardo configuracion por
	 * default.
	 */
	if (!seCargo) {
		archivo.setAtributo(ATRIBUTO_DIRECCION, SERVER_IP_DEFAULT);
		archivo.setAtributo(ATRIBUTO_PUERTO, cft::uintToString(PUERTO_DEFAULT));
		archivo.guardar();
		this->serverIp = SERVER_IP_DEFAULT;
		this->port = PUERTO_DEFAULT;
	} else {
		std::string direccion = archivo.getAtributo(ATRIBUTO_DIRECCION);
		std::string puerto = archivo.getAtributo(ATRIBUTO_PUERTO);
		if (!direccion.empty() && !puerto.empty()) {
			this->serverIp = direccion;
			this->port = cft::stringToUint(puerto);
		} else {
			this->serverIp = SERVER_IP_DEFAULT;
			this->port = PUERTO_DEFAULT;
		}
	}
}

void Client::guardarXML(std::string datosXMLNivel) const {
	XMLDocument doc;
	doc.Parse(datosXMLNivel.c_str(), 0, TIXML_ENCODING_UTF8);
	doc.SaveFile(this->rutaNivelRecibido);
}
