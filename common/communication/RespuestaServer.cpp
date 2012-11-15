// Header Include.
#include "RespuestaServer.h"

// C++ Library Includes.
#include <sstream>

// DEFINICIONES DE CHAR A ALMACENAR PARA IDENTIFICAR EL TIPO DE RESPUESTA.
#define C_TABLA_RECORDS		'R'
#define C_LISTA_MUNDOS		'M'
#define C_LISTA_PARTIDAS	'P'
#define C_OK_UNIRSE			'U'
#define C_ERROR_UNIRSE		'E'

RespuestaServer::RespuestaServer(RespuestaServidor tipo) {
	this->tipo = tipo;
	this->datos.clear();
}

RespuestaServer::RespuestaServer(RespuestaServidor tipo,
		const std::string& datos) {
	this->tipo = tipo;
	this->datos = datos;
}

RespuestaServer::~RespuestaServer() { }

std::string RespuestaServer::serealizar() const {
	std::ostringstream msj;
	// De acuerdo al tipo de respuesta, realizo la serializacion adecuada.
	switch (this->tipo) {
	case TablaRecords:
		// Agrego el identificador y los datos de la tabla de records
		msj << C_TABLA_RECORDS << '|' << this->datos << '|';
		break;
	case ListaMundos:
		// Agrego el identificador y la lista de mundos
		msj << C_LISTA_MUNDOS << '|' << this->datos << '|';
		break;
	case ListaPartidas:
		// Agrego el identificador y la lista de partidas
		msj << C_LISTA_PARTIDAS << '|' << this->datos << '|';
		break;
	case OKUnirsePartida:
		// Agrego el identificador.
		msj << C_OK_UNIRSE << '|';
		break;
	case ErrorUnirsePartida:
		// Agrego el identificador.
		msj << C_ERROR_UNIRSE << '|';
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
	if (msj[1] != '|') {
		this->tipo = RespuestaNoDefinida;
		return;
	}
	// Obtengo el primer caracter
	char c = msj[0];
	switch (c) {
	case C_TABLA_RECORDS:
		this->tipo = TablaRecords;
		this->decodificarDatos(mensaje);
		break;
	case C_LISTA_MUNDOS:
		this->tipo = ListaMundos;
		this->decodificarDatos(mensaje);
		break;
	case C_LISTA_PARTIDAS:
		this->tipo = ListaPartidas;
		this->decodificarDatos(mensaje);
		break;
	case C_OK_UNIRSE:
		this->tipo = OKUnirsePartida;
		break;
	case C_ERROR_UNIRSE:
		this->tipo = ErrorUnirsePartida;
		break;
	default:
		this->tipo = RespuestaNoDefinida;
		break;
	}
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
	while ((c != '|') && (c != '\0')) {
		sDatos += c;
		i++;
		c = cadena[i];
	}
	this->datos = sDatos;
}
