// Header Include.
#include "MensajeServer.h"

// C++ Library Includes.
#include <sstream>

// DEFINICIONES DE CHAR A ALMACENAR PARA IDENTIFICAR EL COMANDO ENVIADO.
#define CMS_CARGAR_NIVEL		'C'
#define CMS_EVENTO				'E'
#define CMS_FINALIZAR_PARTIDA	'F'

MensajeServer::MensajeServer(ComandoServer comando) {
	this->comando = comando;
	this->datos.clear();
	this->evento = NULL;
}

MensajeServer::~MensajeServer() {
	if (evento != NULL) {
		delete evento;
	}
}

std::string MensajeServer::serealizar() const {
	std::ostringstream msj;
	// De acuerdo al comando, realizo la serializacion adecuada.
	switch (this->comando) {
	case MS_CARGAR_NIVEL:
		msj << CMS_CARGAR_NIVEL << '|';
		break;
	case MS_EVENTO:
		msj << CMS_EVENTO << '|';
		break;
	case MS_FINALIZAR_PARTIDA:
		msj << CMS_FINALIZAR_PARTIDA << '|';
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
	const char* msj = mensaje.c_str();
	/* Verifico si en la segunda posicion se encuentra el delimitador.
	 * Si no se encuentra, cargo el mensaje como no definido.
	 */
	if (msj[1] != '|') {
		this->comando = MS_NO_DEFINIDO;
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
		break;
	case CMS_FINALIZAR_PARTIDA:
		this->comando = MS_FINALIZAR_PARTIDA;
		break;
	default:
		this->comando = MS_NO_DEFINIDO;
		break;
	}
}

ComandoServer MensajeServer::getComando() const {
	return this->comando;
}
