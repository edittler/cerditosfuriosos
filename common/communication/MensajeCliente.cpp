// Header Include
#include "MensajeCliente.h"

// C++ Library Includes.
#include <sstream>
#include <cstring>

// DEFINICIONES DE CHAR A ALMACENAR PARA IDENTIFICAR EL COMANDO ENVIADO.
#define C_VER_RECORDS		'R'
#define C_CREAR_PARTIDA		'C'
#define C_VER_PARTIDAS		'V'
#define C_UNIR_SEPARTIDA		'U'
#define C_EVENTO			'E'
#define C_DESCONECTAR		'D'

MensajeCliente::MensajeCliente(ComandoCliente comando) {
	this->comando = comando;
	this->partida.clear();
}

MensajeCliente::MensajeCliente(std::string partidaID) {
	this->comando = UnirsePartida;
	this->partida = partidaID;
}

MensajeCliente::~MensajeCliente() { }

std::string MensajeCliente::serealizar() const {
	std::ostringstream msj;
	// De acuerdo al comando, realizo la serializacion adecuada.
	switch (this->comando) {
	case VerRecords:
		msj << C_VER_RECORDS << '|';
		break;
	case CrearPartida:
		msj << C_CREAR_PARTIDA << '|';
		break;
	case VerPartidas:
		msj << C_VER_PARTIDAS << '|';
		break;
	case UnirsePartida:
		msj << C_UNIR_SEPARTIDA << '|';
		// Agrego el ID de partida.
		msj << this->partida << '|';
		break;
	case Desconectar:
		msj << C_DESCONECTAR << '|';
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

void MensajeCliente::deserealizar(const std::string& mensaje) {
	const char* msj = mensaje.c_str();
	/* Verifico si en la segunda posicion se encuentra el delimitador.
	 * Si no se encuentra, cargo el mensaje como no definido.
	 */
	if (msj[1] != '|') {
		this->comando = ComandoNoDefinido;
		return;
	}
	// Obtengo el primer caracter
	char c = msj[0];
	switch (c) {
	case C_VER_RECORDS:
		this->comando = VerRecords;
		break;
	case C_CREAR_PARTIDA:
		this->comando = CrearPartida;
		break;
	case C_VER_PARTIDAS:
		this->comando = VerPartidas;
		break;
	case C_UNIR_SEPARTIDA:
		this->comando = UnirsePartida;
		// Deserealizar el ID de la partida
		this->decodificarPartida(mensaje);
		break;
	case C_DESCONECTAR:
		this->comando = Desconectar;
		break;
	case C_EVENTO:
		this->comando = Evento;
		break;
	default:
		this->comando = ComandoNoDefinido;
		break;
	}
}

ComandoCliente MensajeCliente::getComando() const {
	return comando;
}

void MensajeCliente::decodificarPartida(const std::string& mensaje) {
	// TODO(eze) Implementar.
}
