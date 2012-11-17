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

Evento::Evento(std::string eventoSerealizado) {
	this->pajaro = T_PAJARO_INDEFINIDO;
	this->disparo = T_DISPARO_INDEFINIDO;
	this->deserealizar(eventoSerealizado);
}

Evento::~Evento() { }

std::string Evento::serealizar() const {
	std::ostringstream msj;
	// De acuerdo al tipo de evento, realizo la serializacion adecuada.
	switch (this->evento) {
	case E_PEDIDO_LANZAR_DISPARO:
		/* Si el disparo no es indefinido, agrego el identificador y
		 * la serializacion del disparo.
		 */
		if (this->disparo != T_DISPARO_INDEFINIDO) {
			msj << TE_PEDIDO_LANZAR_DIS << '%' << this->serializarDisparo();
		}
		break;
	case E_CORRER_TICK:
		// Agrego el identificador.
		msj << TE_CORRER_TICK << '%';
		break;
	case E_LANZAR_PAJARO:
		/* Si el pajaro no es indefinido, agrego el identificador y
		 * la serializacion del pajaro.
		 */
		if (this->pajaro != T_PAJARO_INDEFINIDO) {
			msj << TE_LANZAR_PAJARO << '%' << this->serializarPajaro();
		}
		break;
	case E_LANZAR_DISPARO:
		/* Si el disparo no es indefinido, agrego el identificador y
		 * la serializacion del disparo.
		 */
		if (this->disparo != T_DISPARO_INDEFINIDO) {
			msj << TE_LANZAR_HUEVO << '%' << this->serializarDisparo();
		}
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
	/* Si el disparo no es indefinido, agrego la posicion a disparar
	 * o inicial de disparo.
	 */
	if (this->disparo != T_DISPARO_INDEFINIDO) {
		msj << this->serializarPunto() << '%';
		// Si el evento es LANZAR_DISPARO, debo cargar la velocidad
		if (this->evento == E_LANZAR_DISPARO) {
			msj << this->serializarVelocidad() << '%';
		}
	}
	// Retorna el string.
	return msj.str();
}

std::string Evento::serializarPajaro() const {
	std::ostringstream msj;
	// De acuerdo al tipo de pajaro, realizo la serializacion adecuada.
	switch (this->pajaro) {
	case T_PAJARO_ROJO:
		msj << TP_ROJO << '%';		// Agrego el identificador de pajaro.
		break;
	case T_PAJARO_VERDE:
		msj << TP_VERDE << '%';		// Agrego el identificador de pajaro.
		break;
	case T_PAJARO_AZUL:
		msj << TP_AZUL << '%';		// Agrego el identificador de pajaro.
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
		msj << this->serializarPunto() << '%';
		// Agrego la velocidad inicial de lanzamiento del pajaro
		msj << this->serializarVelocidad() << '%';
	}
	// Retorna el string.
	return msj.str();
}

std::string Evento::serializarPunto() const {
	std::ostringstream valX, valY, sPunto;
	valX.imbue(std::locale("C"));
	valY.imbue(std::locale("C"));
	valX << this->punto.x;
	valY << this->punto.y;
	sPunto << valX.str() << '&' << valY.str() << '&';
	return sPunto.str();
}

std::string Evento::serializarVelocidad() const {
	std::ostringstream valX, valY, sVelocidad;
	valX.imbue(std::locale("C"));
	valY.imbue(std::locale("C"));
	valX << this->velocidad.x;
	valY << this->velocidad.y;
	sVelocidad << valX.str() << '&' << valY.str() << '&';
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
	while ((c != '%') && (c != '\0')) {
		cadena += c;
		i++;
		c = msj[i];
	}
	this->decodificarPunto(cadena);
	// Si el tipo de evento es lanzamiento de disparo, decodifico la velocidad.
	if (this->evento == E_LANZAR_DISPARO) {
		cadena.clear();
		i++;
		c = msj[i];
		while ((c != '%') && (c != '\0')) {
			cadena += c;
			i++;
			c = msj[i];
		}
		this->decodificarVelocidad(cadena);
	}
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
	while ((c != '%') && (c != '\0')) {
		cadena += c;
		i++;
		c = msj[i];
	}
	this->decodificarPunto(cadena);
	// decodifico la velocidad.
	cadena.clear();
	i++;
	c = msj[i];
	while ((c != '%') && (c != '\0')) {
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
	while ((mensaje[i] != '&') && (mensaje[i] != '\0')) {
		sX += mensaje[i];
		i++;
	}
	// Obtengo el atributo y
	std::string sY;
	i++;
	while ((mensaje[i] != '&') && (mensaje[i] != '\0')) {
		sY += mensaje[i];
		i++;
	}
	std::istringstream valX(sX);
	std::istringstream valY(sY);
	// Seteo la configuracion regional defaul de C++ para dichos streams.
	valX.imbue(std::locale("C"));
	valY.imbue(std::locale("C"));
	valX >> this->punto.x;
	valY >> this->punto.y;
}

void Evento::decodificarVelocidad(const std::string& mensaje) {
	// Obtengo el atributo x
	std::string sX;
	int i = 0;
	while ((mensaje[i] != '&') && (mensaje[i] != '\0')) {
		sX += mensaje[i];
		i++;
	}
	// Obtengo el atributo y
	std::string sY;
	i++;
	while ((mensaje[i] != '&') && (mensaje[i] != '\0')) {
		sY += mensaje[i];
		i++;
	}
	std::istringstream valX(sX);
	std::istringstream valY(sY);
	// Seteo la configuracion regional defaul de C++ para dichos streams.
	valX.imbue(std::locale("C"));
	valY.imbue(std::locale("C"));
	valX >> this->velocidad.x;
	valY >> this->velocidad.y;
}
