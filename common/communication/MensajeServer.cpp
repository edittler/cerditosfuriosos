// Header Include.
#include "MensajeServer.h"

// C++ Library Includes.
#include <sstream>

// DEFINICIONES DE CHAR A ALMACENAR PARA IDENTIFICAR EL COMANDO ENVIADO.
#define CMS_CARGAR_NIVEL		'C'
#define CMS_EVENTO				'E'
#define CMS_FINALIZAR_PARTIDA	'F'

// DEFINICION DEL DELIMITADOR DE COMANDOS DEL MENSAJE SERVER
#define MS_DELIMITADOR	'|'

MensajeServer::MensajeServer(ComandoServer comando) {
	this->comando = comando;
	this->datos.clear();
}

MensajeServer::MensajeServer(Evento evento) {
	this->comando = MS_EVENTO;
	this->evento = evento;
}

MensajeServer::~MensajeServer() { }

std::string MensajeServer::serealizar() const {
	std::ostringstream msj;
	// De acuerdo al comando, realizo la serializacion adecuada.
	switch (this->comando) {
	case MS_CARGAR_NIVEL:
		msj << CMS_CARGAR_NIVEL << MS_DELIMITADOR;
		break;
	case MS_EVENTO:
		msj << CMS_EVENTO << MS_DELIMITADOR << this->evento.serealizar() <<
				MS_DELIMITADOR;
		break;
	case MS_FINALIZAR_PARTIDA:
		msj << CMS_FINALIZAR_PARTIDA << MS_DELIMITADOR;
		// Agrego el ID de partida.
		break;
	default:
		// Para el caso por defaul, no realizo nada.
		break;
	}
	// Completa el string con un terminador de linea
	msj << '\n';
	// Retorna el string.
	return msj.str();
}

void MensajeServer::deserealizar(const std::string& mensaje) {
	// Si la cadena está vacia, deserializo como mensaje indefinido
	if (mensaje.empty()) {
		this->comando = MS_INDEFINIDO;
		return;
	}
	const char* msj = mensaje.c_str();
	/* Verifico si en la segunda posicion se encuentra el delimitador.
	 * Si no se encuentra, cargo el mensaje como no definido.
	 */
	if (msj[1] != MS_DELIMITADOR) {
		this->comando = MS_INDEFINIDO;
		return;
	}
	// Obtengo el primer caracter
	char c = msj[0];
	switch (c) {
	case CMS_CARGAR_NIVEL:
		this->comando = MS_CARGAR_NIVEL;
		break;
	case CMS_EVENTO:
		this->comando = MS_EVENTO;
		this->deserealizarEvento(mensaje);
		break;
	case CMS_FINALIZAR_PARTIDA:
		this->comando = MS_FINALIZAR_PARTIDA;
		break;
	default:
		this->comando = MS_INDEFINIDO;
		break;
	}
}

void MensajeServer::setEvento(Evento evento) {
	this->evento = evento;
}

ComandoServer MensajeServer::getComando() const {
	return this->comando;
}

Evento MensajeServer::getEvento() const {
	return evento;
}

void MensajeServer::deserealizarEvento(const std::string& mensaje) {
	const char* msj = mensaje.c_str();
	std::string sEvento;
	int i = 2;
	char c = msj[i];
	while((c != MS_DELIMITADOR) && (c != '\0')) {
		sEvento += c;
		i++;
		c = msj[i];
	}
	this->evento.deserealizar(sEvento);
}
