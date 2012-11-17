// Header Include.
#include "Evento.h"

// C++ Library Includes.
#include <sstream>

// DEFINICIONES DE CHAR A ALMACENAR PARA IDENTIFICAR EL TIPO DE EVENTO.
#define TE_PEDIDO_LANZAR_DIS	'D'
#define TE_LANZAR_PAJARO		'P'
#define TE_LANZAR_HUEVO			'H'
#define TE_FIN_NIVEL			'F'

// DEFINICIONES DE CHAR A ALMACENAR PARA IDENTIFICAR EL TIPO DE PAJARO.
#define TP_ROJO		'R'
#define TP_VERDE	'V'
#define TP_AZUL		'A'

// DEFINICIONES DE CHAR A ALMACENAR PARA IDENTIFICAR EL TIPO DE DISPARO.
#define TD_HBLANCO		'B'
#define TD_HCODORNIZ	'C'
#define TD_HPOCHE		'O'
#define TD_HRELOJ		'E'

Evento::Evento(TipoEvento evento) {
	this->evento = evento;
	this->pajaro = T_PAJARO_INDEFINIDO;
	this->disparo = T_DISPARO_INDEFINIDO;
}

Evento::Evento(TipoDisparo tDisparo, Punto2D puntoADisparar) {
	this->evento = E_PEDIDO_LANZAR_DISPARO;
	this->pajaro = T_PAJARO_INDEFINIDO;
	this->disparo = tDisparo;
	this->punto = puntoADisparar;
}

Evento::Evento(TipoPajaro tPajaro, Punto2D puntoInicial, Velocidad2D velInicial) {
	this->evento = E_LANZAR_PAJARO;
	this->pajaro = tPajaro;
	this->disparo = T_DISPARO_INDEFINIDO;
	this->punto = puntoInicial;
	this->velocidad	= velInicial;
}

Evento::Evento(TipoDisparo tDisparo, Punto2D puntoInicial, Velocidad2D velInicial) {
	this->evento = E_LANZAR_DISPARO;
	this->pajaro = T_PAJARO_INDEFINIDO;
	this->disparo = tDisparo;
	this->punto = puntoInicial;
	this->velocidad = velInicial;
}

Evento::~Evento() { }

std::string Evento::serealizar() const {
	std::ostringstream msj;
	// De acuerdo al tipo de evento, realizo la serializacion adecuada.
	switch (this->evento) {
	case E_PEDIDO_LANZAR_DISPARO:
		// Agrego el identificador y la serializacion del disparo.
		msj << TE_PEDIDO_LANZAR_DIS << '%' << this->serializarDisparo() << '%';
		break;
	case E_LANZAR_PAJARO:
		// Agrego el identificador y la serializacion de pajaro
		msj << TE_LANZAR_PAJARO << '%' << this->serializarPajaro() << '%';
		break;
	case E_LANZAR_DISPARO:
		// Agrego el identificador y la serializacion del disparo.
		msj << TE_LANZAR_HUEVO << '%' << this->serializarDisparo() << '%';
		break;
	case E_FIN_NIVEL:
		// Agrego el identificador.
		msj << TE_FIN_NIVEL << '%';
		break;
	default:
		// Para el caso por defaul, no realizo nada.
		break;
	}
	// Retorna el string.
	return msj.str();
}

void Evento::deserealizar(const std::string& mensaje) {
	const char* msj = mensaje.c_str();
	/* Verifico si en la segunda posicion se encuentra el delimitador.
	 * Si no se encuentra, cargo el mensaje como no definido.
	 */
	if (msj[1] != '%') {
		this->evento = E_INDEFINIDO;
		return;
	}
	// Obtengo el primer caracter
	char c = msj[0];
	switch (c) {
	case TE_PEDIDO_LANZAR_DIS:
		this->evento = E_PEDIDO_LANZAR_DISPARO;
		this->decodificarDisparo(mensaje);
		break;
	case TE_LANZAR_PAJARO:
		this->evento = E_LANZAR_PAJARO;
		this->decodificarPajaro(mensaje);
		break;
	case TE_LANZAR_HUEVO:
		this->evento = E_LANZAR_DISPARO;
		this->decodificarDisparo(mensaje);
		break;
	case TE_FIN_NIVEL:
		this->evento = E_FIN_NIVEL;
		break;
	default:
		this->evento = E_INDEFINIDO;
		break;
	}
}

TipoEvento Evento::getTipoEvento() const {
	return evento;
}

TipoPajaro Evento::getTipoPajaro() const {
	/* Si el evento es lanzar pajaro, retorno el tipo almacenado.
	 * Sino, retorno tipo no definido.
	 */
	if (evento == E_LANZAR_PAJARO) {
		return pajaro;
	} else {
		return T_PAJARO_INDEFINIDO;
	}
}

TipoDisparo Evento::getTipoDisparo() const {
	/* Si el evento es lanzar disparo o solicitud, retorno el tipo almacenado.
	 * Sino, retorno tipo no definido.
	 */
	if ((evento == E_PEDIDO_LANZAR_DISPARO) || (evento == E_LANZAR_DISPARO)) {
		return disparo;
	} else {
		return T_DISPARO_INDEFINIDO;
	}
}

Punto2D Evento::getPunto() const {
	return punto;
}

Velocidad2D Evento::getVelocidad() const {
	return velocidad;
}

std::string Evento::serializarDisparo() const {
	std::ostringstream msj;
	// De acuerdo al tipo de disparo, realizo la serializacion adecuada.
	switch (this->disparo) {
	case T_HUEVO_BLANCO:
		msj << TD_HBLANCO << '%';		// Agrego el identificador de disparo.
		break;
	case T_HUEVO_CODORNIZ:
		msj << TD_HCODORNIZ << '%';		// Agrego el identificador de disparo.
		break;
	case T_HUEVO_POCHE:
		msj << TD_HPOCHE << '%';		// Agrego el identificador de disparo.
		break;
	case T_HUEVO_RELOJ:
		msj << TD_HRELOJ << '%';		// Agrego el identificador de disparo.
		break;
	default:
		// Para el caso por defaul, no realizo nada.
		break;
	}
	// Agrego la posicion a disparar o inicial de disparo
	msj << this->serializarPunto();
	// Si el evento es LANZAR_DISPARO, debo cargar la velocidad
	if (this->evento == E_LANZAR_DISPARO) {
		msj << this->serializarVelocidad();
	}
	// Retorna el string.
	return msj.str();
}

std::string Evento::serializarPajaro() const {
	// TODO(eze) Implementar.
	return "Pajaro";
}

std::string Evento::serializarPunto() const {
	// TODO(eze) Implementar.
	return "Punto";
}

std::string Evento::serializarVelocidad() const {
	// TODO(eze) Implementar.
	return "Velocidad";
}

void Evento::decodificarDisparo(const std::string& mensaje) {
	// TODO(eze) Implementar
}

void Evento::decodificarPajaro(const std::string& mensaje) {
	// TODO(eze) Implementar
}

void Evento::decodificarPunto(const std::string& mensaje) {
	// TODO(eze) Implementar
}

void Evento::decodificarVelocidad(const std::string& mensaje) {
	// TODO(eze) Implementar
}
