// Header Include.
#include "Evento.h"

// C++ Library Includes.
#include <sstream>
#include <iostream>  // TODO PROVISORIO

// DEFINICIONES DE CHAR A ALMACENAR PARA IDENTIFICAR EL TIPO DE EVENTO.
#define TE_PEDIDO_LANZAR_DIS	'D'
#define TE_CORRER_TICK			'T'
#define TE_LANZAR_PAJARO		'P'
#define TE_LANZAR_HUEVO			'H'
#define TE_FIN_NIVEL			'F'

// DEFINICIONES DE CHAR A USAR COMO DELIMITADORES
#define E_DELIMITADOR_PARAMETRO '%'
#define E_DELIMITADOR_NUMERO '&'

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
	this->set(evento);
}

Evento::Evento(const Evento& evento) {
	this->evento = evento.evento;
	this->pajaro = evento.pajaro;
	this->disparo = evento.disparo;
	this->punto = evento.punto;
	this->velocidad = evento.velocidad;
}

Evento::Evento(TipoPajaro tPajaro, Punto2D puntoInicial, Velocidad2D velInicial) {
	this->set(tPajaro, puntoInicial, velInicial);
}

Evento::Evento(TipoDisparo tDisparo, Punto2D puntoInicial, Velocidad2D velInicial) {
	this->set(tDisparo, puntoInicial, velInicial);
}

Evento::Evento(std::string eventoSerealizado) {
	this->pajaro = T_PAJARO_INDEFINIDO;
	this->disparo = T_DISPARO_INDEFINIDO;
	this->deserealizar(eventoSerealizado);
}

Evento::~Evento() { }

Evento& Evento::operator=(const Evento& evento) {
	this->evento = evento.evento;
	this->pajaro = evento.pajaro;
	this->disparo = evento.disparo;
	this->punto = evento.punto;
	this->velocidad = evento.velocidad;
	return *this;
}

std::string Evento::serealizar() const {
	std::ostringstream msj;
	// De acuerdo al tipo de evento, realizo la serializacion adecuada.
	switch (this->evento) {
	case E_PEDIDO_LANZAR_DISPARO:
		/* Si el disparo no es indefinido, agrego el identificador y
		 * la serializacion del disparo.
		 */
		if (this->disparo != T_DISPARO_INDEFINIDO) {
			msj << TE_PEDIDO_LANZAR_DIS << E_DELIMITADOR_PARAMETRO <<
					this->serializarDisparo();
		}
		break;
	case E_CORRER_TICK:
		// Agrego el identificador.
		msj << TE_CORRER_TICK << E_DELIMITADOR_PARAMETRO;
		break;
	case E_LANZAR_PAJARO:
		/* Si el pajaro no es indefinido, agrego el identificador y
		 * la serializacion del pajaro.
		 */
		if (this->pajaro != T_PAJARO_INDEFINIDO) {
			msj << TE_LANZAR_PAJARO << E_DELIMITADOR_PARAMETRO <<
					this->serializarPajaro();
		}
		break;
	case E_LANZAR_DISPARO:
		/* Si el disparo no es indefinido, agrego el identificador y
		 * la serializacion del disparo.
		 */
		if (this->disparo != T_DISPARO_INDEFINIDO) {
			msj << TE_LANZAR_HUEVO << E_DELIMITADOR_PARAMETRO <<
					this->serializarDisparo();
		}
		break;
	case E_FIN_NIVEL:
		// Agrego el identificador.
		msj << TE_FIN_NIVEL << E_DELIMITADOR_PARAMETRO;
		break;
	default:
		// Para el caso por defaul, no realizo nada.
		break;
	}
	// Retorna el string.
	return msj.str();
}

void Evento::deserealizar(const std::string& mensaje) {
	// Si la cadena está vacia, deserializo como evento indefinido
	if (mensaje.empty()) {
		this->evento = E_INDEFINIDO;
		return;
	}
	// Obtengo la cadena de caracteres asociada al mensaje.
	const char* msj = mensaje.c_str();
	/* Verifico si en la segunda posicion se encuentra el delimitador.
	 * Si no se encuentra, cargo el mensaje como no definido.
	 */
	if (msj[1] != E_DELIMITADOR_PARAMETRO) {
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
	case TE_CORRER_TICK:
		this->evento = E_CORRER_TICK;
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

void Evento::set(TipoEvento evento) {
	this->evento = evento;
}

void Evento::set(TipoPajaro tPajaro, Punto2D puntoInicial, Velocidad2D velInicial) {
	this->evento = E_LANZAR_PAJARO;
	this->pajaro = tPajaro;
	this->disparo = T_DISPARO_INDEFINIDO;
	this->punto = puntoInicial;
	this->velocidad	= velInicial;
}

void Evento::set(TipoDisparo tDisparo, Punto2D puntoInicial, Velocidad2D velInicial) {
	this->evento = E_LANZAR_DISPARO;
	this->pajaro = T_PAJARO_INDEFINIDO;
	this->disparo = tDisparo;
	this->punto = puntoInicial;
	this->velocidad = velInicial;
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
		msj << TD_HBLANCO << E_DELIMITADOR_PARAMETRO;
		break;
	case T_HUEVO_CODORNIZ:
		msj << TD_HCODORNIZ << E_DELIMITADOR_PARAMETRO;
		break;
	case T_HUEVO_POCHE:
		msj << TD_HPOCHE << E_DELIMITADOR_PARAMETRO;
		break;
	case T_HUEVO_RELOJ:
		msj << TD_HRELOJ << E_DELIMITADOR_PARAMETRO;
		break;
	default:
		// Para el caso por defaul, no realizo nada.
		break;
	}
	/* Si el disparo no es indefinido, agrego la posicion a disparar
	 * o inicial de disparo.
	 */
	if (this->disparo != T_DISPARO_INDEFINIDO) {
		msj << this->serializarPunto() << E_DELIMITADOR_PARAMETRO;
		msj << this->serializarVelocidad() << E_DELIMITADOR_PARAMETRO;
	}
	// Retorna el string.
	return msj.str();
}

std::string Evento::serializarPajaro() const {
	std::ostringstream msj;
	// De acuerdo al tipo de pajaro, realizo la serializacion adecuada.
	switch (this->pajaro) {
	case T_PAJARO_ROJO:
		msj << TP_ROJO << E_DELIMITADOR_PARAMETRO;
		break;
	case T_PAJARO_VERDE:
		msj << TP_VERDE << E_DELIMITADOR_PARAMETRO;
		break;
	case T_PAJARO_AZUL:
		msj << TP_AZUL << E_DELIMITADOR_PARAMETRO;
		break;
	default:
		// Para el caso por defaul, no realizo nada.
		break;
	}
	/* Si el pajaro no es indefinido, agrego la posicion y velocidad inicial
	 * de lanzamiento.
	 */
	if (this->pajaro != T_PAJARO_INDEFINIDO) {
		// Agrego la posicion inicial de lanzamiento del pajaro
		msj << this->serializarPunto() << E_DELIMITADOR_PARAMETRO;
		// Agrego la velocidad inicial de lanzamiento del pajaro
		msj << this->serializarVelocidad() << E_DELIMITADOR_PARAMETRO;
	}
	// Retorna el string.
	return msj.str();
}

std::string Evento::serializarPunto() const {
	std::ostringstream sPunto;
	std::string valX, valY;
	valX = this->floatToString(this->punto.x);
	valY = this->floatToString(this->punto.y);
	sPunto << valX << E_DELIMITADOR_NUMERO << valY << E_DELIMITADOR_NUMERO;
	return sPunto.str();
}

std::string Evento::serializarVelocidad() const {
	std::ostringstream sVelocidad;
	std::string valX, valY;
	valX = this->floatToString(this->velocidad.x);
	valY = this->floatToString(this->velocidad.y);
	sVelocidad << valX << E_DELIMITADOR_NUMERO << valY << E_DELIMITADOR_NUMERO;
	return sVelocidad.str();
}

void Evento::decodificarDisparo(const std::string& mensaje) {
	const char* msj = mensaje.c_str();
	// Obtengo el tipo de disparo y aigno el atributo correspondiente.
	char tipoDisparo = msj[2];
	switch (tipoDisparo) {
	case TD_HBLANCO:
		this->disparo = T_HUEVO_BLANCO;
		break;
	case TD_HCODORNIZ:
		this->disparo = T_HUEVO_CODORNIZ;
		break;
	case TD_HPOCHE:
		this->disparo = T_HUEVO_POCHE;
		break;
	case TD_HRELOJ:
		this->disparo = T_HUEVO_RELOJ;
		break;
	default:
		this->disparo = T_DISPARO_INDEFINIDO;
		break;
	}
	// Decodifico la posicion.
	int i = 4;
	char c = msj[i];
	std::string cadena;
	cadena.clear();
	while ((c != E_DELIMITADOR_PARAMETRO) && (c != '\0')) {
		cadena += c;
		i++;
		c = msj[i];
	}
	this->decodificarPunto(cadena);
	// Decodifico la velocidad.
	cadena.clear();
	i++;
	c = msj[i];
	while ((c != E_DELIMITADOR_PARAMETRO) && (c != '\0')) {
		cadena += c;
		i++;
		c = msj[i];
	}
	this->decodificarVelocidad(cadena);
}

void Evento::decodificarPajaro(const std::string& mensaje) {
	const char* msj = mensaje.c_str();
	// Obtengo el tipo de pajaro y aigno el atributo correspondiente.
	char tipoPajaro = msj[2];
	switch (tipoPajaro) {
	case TP_ROJO:
		this->pajaro = T_PAJARO_ROJO;
		break;
	case TP_VERDE:
		this->pajaro = T_PAJARO_VERDE;
		break;
	case TP_AZUL:
		this->pajaro = T_PAJARO_AZUL;
		break;
	default:
		this->pajaro = T_PAJARO_INDEFINIDO;
		break;
	}
	// Decodifico la posicion.
	int i = 4;
	char c = msj[i];
	std::string cadena;
	cadena.clear();
	while ((c != E_DELIMITADOR_PARAMETRO) && (c != '\0')) {
		cadena += c;
		i++;
		c = msj[i];
	}
	this->decodificarPunto(cadena);
	// decodifico la velocidad.
	cadena.clear();
	i++;
	c = msj[i];
	while ((c != E_DELIMITADOR_PARAMETRO) && (c != '\0')) {
		cadena += c;
		i++;
		c = msj[i];
	}
	this->decodificarVelocidad(cadena);
}

void Evento::decodificarPunto(const std::string& mensaje) {
	// Obtengo el atributo x
	std::string sX;
	int i = 0;
	while ((mensaje[i] != E_DELIMITADOR_NUMERO) && (mensaje[i] != '\0')) {
		sX += mensaje[i];
		i++;
	}
	// Obtengo el atributo y
	std::string sY;
	i++;
	while ((mensaje[i] != E_DELIMITADOR_NUMERO) && (mensaje[i] != '\0')) {
		sY += mensaje[i];
		i++;
	}
	this->punto.x = this->stringToFloat(sX);
	this->punto.y = this->stringToFloat(sY);
}

void Evento::decodificarVelocidad(const std::string& mensaje) {
	// Obtengo el atributo x
	std::string sX;
	int i = 0;
	while ((mensaje[i] != E_DELIMITADOR_NUMERO) && (mensaje[i] != '\0')) {
		sX += mensaje[i];
		i++;
	}
	// Obtengo el atributo y
	std::string sY;
	i++;
	while ((mensaje[i] != E_DELIMITADOR_NUMERO) && (mensaje[i] != '\0')) {
		sY += mensaje[i];
		i++;
	}
	this->velocidad.x = this->stringToFloat(sX);
	this->velocidad.y = this->stringToFloat(sY);
}

std::string Evento::floatToString(const float valor) const {
	std::ostringstream val;
	val.imbue(std::locale("C"));
	val << valor;
	return val.str();
}

float Evento::stringToFloat(const std::string cadena) const {
	std::istringstream val(cadena);
	val.imbue(std::locale("C"));
	float valor;
	val >> valor;
	return valor;
}
