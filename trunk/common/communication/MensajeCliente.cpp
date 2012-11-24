// Header Include
#include "MensajeCliente.h"

// C++ Library Includes.
#include <sstream>

// DEFINICIONES DE CHAR A ALMACENAR PARA IDENTIFICAR EL COMANDO ENVIADO.
#define C_VER_RECORDS		'R'
#define C_VER_MUNDOS		'M'
#define C_CREAR_PARTIDA		'C'
#define C_VER_PARTIDAS		'V'
#define C_UNIRSE_PARTIDA	'U'
#define C_EVENTO			'E'
#define C_ABANDONAR_PARTIDA	'A'
#define C_DESCONECTAR		'D'

// DEFINICIONES DE CHAR A USAR COMO DELIMITADORES
#define MC_DELIMITADOR '|'

MensajeCliente::MensajeCliente(ComandoCliente comando) {
	this->set(comando);
}

MensajeCliente::MensajeCliente(std::string idMundo, std::string nombrePartida) {
	this->set(idMundo, nombrePartida);
}

MensajeCliente::MensajeCliente(std::string idPartida) {
	this->set(idPartida);
}

MensajeCliente::MensajeCliente(Evento evento) {
	this->comando = MC_EVENTO;
	this->evento = evento;
}

MensajeCliente::~MensajeCliente() { }

std::string MensajeCliente::serealizar() const {
	std::ostringstream msj;
	// De acuerdo al comando, realizo la serializacion adecuada.
	switch (this->comando) {
	case MC_VER_RECORDS:
		msj << C_VER_RECORDS << MC_DELIMITADOR;
		break;
	case MC_VER_MUNDOS:
		msj << C_VER_MUNDOS << MC_DELIMITADOR;
		break;
	case MC_CREAR_PARTIDA:
		msj << C_CREAR_PARTIDA << MC_DELIMITADOR;
		// Agrego el ID del mundo.
		msj << this->id << MC_DELIMITADOR;
		// Agrego el nombre elegido para la partida
		msj << this->nombre << MC_DELIMITADOR;
		break;
	case MC_VER_PARTIDAS:
		msj << C_VER_PARTIDAS << MC_DELIMITADOR;
		break;
	case MC_UNIRSE_PARTIDA:
		msj << C_UNIRSE_PARTIDA << MC_DELIMITADOR;
		// Agrego el ID de partida.
		msj << this->id << MC_DELIMITADOR;
		break;
	case MC_EVENTO:
		msj << C_EVENTO << MC_DELIMITADOR;
		// Agrego el evento;
		msj << this->evento.serealizar() << MC_DELIMITADOR;
		break;
	case MC_ABANDONAR_PARTIDA:
		msj << C_ABANDONAR_PARTIDA << MC_DELIMITADOR;
		break;
	case MC_DESCONECTAR:
		msj << C_DESCONECTAR << MC_DELIMITADOR;
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
	if (msj[1] != MC_DELIMITADOR) {
		this->comando = MC_INDEFINIDO;
		return;
	}
	// Obtengo el primer caracter
	char c = msj[0];
	switch (c) {
	case C_VER_RECORDS:
		this->comando = MC_VER_RECORDS;
		break;
	case C_VER_MUNDOS:
		this->comando = MC_VER_MUNDOS;
		break;
	case C_CREAR_PARTIDA:
		this->comando = MC_CREAR_PARTIDA;
		// Deserealizo el id del mundo y nombre de la partida.
		this->decodificarParametros(mensaje);
		break;
	case C_VER_PARTIDAS:
		this->comando = MC_VER_PARTIDAS;
		break;
	case C_UNIRSE_PARTIDA:
		this->comando = MC_UNIRSE_PARTIDA;
		// Deserealizar el ID de la partida
		this->decodificarParametros(mensaje);
		break;
	case C_ABANDONAR_PARTIDA:
		this->comando = MC_ABANDONAR_PARTIDA;
		break;
	case C_DESCONECTAR:
		this->comando = MC_DESCONECTAR;
		break;
	case C_EVENTO:
		this->comando = MC_EVENTO;
		this->deserealizarEvento(mensaje);
		break;
	default:
		this->comando = MC_INDEFINIDO;
		break;
	}
}

void MensajeCliente::set(ComandoCliente comando) {
	this->comando = comando;
	this->id.clear();
	this->nombre.clear();
}

void MensajeCliente::set(std::string idMundo, std::string nombrePartida) {
	this->comando = MC_CREAR_PARTIDA;
	this->id = idMundo;
	this->nombre = nombrePartida;
}

void MensajeCliente::set(std::string idPartida) {
	this->comando = MC_UNIRSE_PARTIDA;
	this->id = idPartida;
	this->nombre.clear();
}

void MensajeCliente::set(Evento evento) {
	this->comando = MC_EVENTO;
	this->id.clear();
	this->nombre.clear();
	this->evento = evento;
}

ComandoCliente MensajeCliente::getComando() const {
	return comando;
}

std::string MensajeCliente::getID() const {
	return id;
}

std::string MensajeCliente::getNombrePartida() const {
	return this->nombre;
}

Evento MensajeCliente::getEvento() const {
	return evento;
}

void MensajeCliente::decodificarParametros(const std::string& mensaje) {
	const char* msj = mensaje.c_str();
	std::string tmp;
	int i = 2;
	char c = msj[i];
	while((c != MC_DELIMITADOR) && (c != '\0')) {
		tmp += c;
		i++;
		c = msj[i];
	}
	this->id = tmp;
	// Si el comando es CREAR_PARTIDA, decodifico el nombre de la partida
	if (this->comando == MC_CREAR_PARTIDA) {
		i++;
		c = msj[i];
		tmp.clear();
		while((c != MC_DELIMITADOR) && (c != '\0')) {
			tmp += c;
			i++;
			c = msj[i];
		}
		this->nombre = tmp;
	}
}

void MensajeCliente::deserealizarEvento(const std::string& mensaje) {
	const char* msj = mensaje.c_str();
	std::string sEvento;
	int i = 2;
	char c = msj[i];
	while((c != MC_DELIMITADOR) && (c != '\0')) {
		sEvento += c;
		i++;
		c = msj[i];
	}
	this->evento.deserealizar(sEvento);
}
