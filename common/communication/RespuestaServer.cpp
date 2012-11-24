// Header Include.
#include "RespuestaServer.h"

// C++ Library Includes.
#include <sstream>

// Project Includes.
#include "CFTools.h"

// DEFINICIONES DE CHAR A ALMACENAR PARA IDENTIFICAR EL TIPO DE RESPUESTA.
#define C_TABLA_RECORDS		'R'
#define C_LISTA_MUNDOS		'M'
#define C_LISTA_PARTIDAS	'P'
#define C_OK_UNIRSE			'U'
#define C_ERROR_UNIRSE		'E'

// DEFINICIONES DE CHAR A USAR COMO DELIMITADORES
#define RS_DELIMITADOR '|'

RespuestaServer::RespuestaServer(RespuestaServidor tipo) {
	this->set(tipo);
}

RespuestaServer::RespuestaServer(RespuestaServidor tipo,
		const std::string& datos) {
	this->set(tipo, datos);
}

RespuestaServer::RespuestaServer(unsigned int idJugador) {
	this->set(idJugador);
}

RespuestaServer::~RespuestaServer() { }

std::string RespuestaServer::serealizar() const {
	std::ostringstream msj;
	// De acuerdo al tipo de respuesta, realizo la serializacion adecuada.
	switch (this->tipo) {
	case RS_TABLA_RECORDS:
		// Agrego el identificador y los datos de la tabla de records
		msj << C_TABLA_RECORDS << RS_DELIMITADOR << this->datos << RS_DELIMITADOR;
		break;
	case RS_LISTA_MUNDOS:
		// Agrego el identificador y la lista de mundos
		msj << C_LISTA_MUNDOS << RS_DELIMITADOR << this->datos << RS_DELIMITADOR;
		break;
	case RS_LISTA_PARTIDAS:
		// Agrego el identificador y la lista de partidas
		msj << C_LISTA_PARTIDAS << RS_DELIMITADOR << this->datos << RS_DELIMITADOR;
		break;
	case RS_UNIRSE_PARTIDA_OK:
		// Agrego el identificador del mensaje y el identificador del jugador.
		msj << C_OK_UNIRSE << RS_DELIMITADOR << cft::uintToString(idJugador) <<
				RS_DELIMITADOR;
		break;
	case RS_UNIRSE_PARTIDA_ERROR:
		// Agrego el identificador.
		msj << C_ERROR_UNIRSE << RS_DELIMITADOR;
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

void RespuestaServer::deserealizar(const std::string& mensaje) {
	const char* msj = mensaje.c_str();
	/* Verifico si en la segunda posicion se encuentra el delimitador.
	 * Si no se encuentra, cargo el mensaje como no definido.
	 */
	if (msj[1] != RS_DELIMITADOR) {
		this->tipo = RS_INDEFINIDA;
		return;
	}
	// Obtengo el primer caracter
	char c = msj[0];
	switch (c) {
	case C_TABLA_RECORDS:
		this->tipo = RS_TABLA_RECORDS;
		this->decodificarDatos(mensaje);
		break;
	case C_LISTA_MUNDOS:
		this->tipo = RS_LISTA_MUNDOS;
		this->decodificarDatos(mensaje);
		break;
	case C_LISTA_PARTIDAS:
		this->tipo = RS_LISTA_PARTIDAS;
		this->decodificarDatos(mensaje);
		break;
	case C_OK_UNIRSE:
		this->tipo = RS_UNIRSE_PARTIDA_OK;
		this->decodificarIDJugador(mensaje);
		break;
	case C_ERROR_UNIRSE:
		this->tipo = RS_UNIRSE_PARTIDA_ERROR;
		break;
	default:
		this->tipo = RS_INDEFINIDA;
		break;
	}
}

void RespuestaServer::set(RespuestaServidor tipo) {
	this->tipo = tipo;
	this->datos.clear();
	this->idJugador = 0;
}

void RespuestaServer::set(RespuestaServidor tipo, const std::string& datos) {
	this->tipo = tipo;
	this->datos = datos;
	this->idJugador = 0;
}

void RespuestaServer::set(unsigned int idJugador) {
	this->tipo = RS_UNIRSE_PARTIDA_OK;
	this->datos.clear();
	this->idJugador = idJugador;
}

RespuestaServidor RespuestaServer::getTipoRespuesta() const {
	return tipo;
}

std::string RespuestaServer::getDatos() const {
	return datos;
}

void RespuestaServer::decodificarDatos(const std::string& mensaje) {
	// Obtengo el mensaje en una cadena de chars.
	const char* cadena = mensaje.c_str();
	// Declaro los string de datos.
	std::string sDatos;
	char c;  // Char para obtener cada caracter
	int i = 2;  // Contador de caracter
	c = cadena[i];  // Obtengo el primer caracter
	// Mientras no encuentre el caracter |
	while ((c != RS_DELIMITADOR) && (c != '\0')) {
		sDatos += c;
		i++;
		c = cadena[i];
	}
	this->datos = sDatos;
}

void RespuestaServer::decodificarIDJugador(const std::string& mensaje) {
	// Obtengo el mensaje en una cadena de chars.
	const char* cadena = mensaje.c_str();
	// Declaro los string de datos.
	std::string sDatos;
	char c;  // Char para obtener cada caracter
	int i = 2;  // Contador de caracter
	c = cadena[i];  // Obtengo el primer caracter
	// Mientras no encuentre el caracter |
	while ((c != RS_DELIMITADOR) && (c != '\0')) {
		sDatos += c;
		i++;
		c = cadena[i];
	}
	this->idJugador = cft::stringToUint(sDatos);
}
