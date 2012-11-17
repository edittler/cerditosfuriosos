#ifndef EVENTO_H_
#define EVENTO_H_
// Hierarchy Include.
#include "Mensaje.h"

// C++ Library Includes.
#include <string>

// Project Includes.
#include "../model/Punto2D.h"
#include "../model/Velocidad2D.h"

/**
 * Enumerado de los tipos de eventos que hay.
 */
enum TipoEvento {
	E_INDEFINIDO,			// Evento indefinido.
	E_PEDIDO_LANZAR_DISPARO,	// Pedido de lanzamiento de huevo.
	E_CORRER_TICK,			// Correr un tick. TODO ver si envia el XML o no.
	E_LANZAR_PAJARO,		// Lanzamiento de pajaro.
	E_LANZAR_DISPARO,		// Lanzamiento de huevo.
	E_FIN_NIVEL				// Fin de nivel.
};

/**
 * Enumerado de los tipos de pájaros que hay en el modelo usados para las
 * comunicaciones mediante la clase Evento.
 */
enum TipoPajaro {
	T_PAJARO_INDEFINIDO,
	T_PAJARO_ROJO,
	T_PAJARO_VERDE,
	T_PAJARO_AZUL
};

/**
 * Enumerado de los tipos de disparos que hay en el modelo usados para las
 * comunicaciones mediante la clase Evento.
 */
enum TipoDisparo {
	T_DISPARO_INDEFINIDO,
	T_HUEVO_BLANCO,
	T_HUEVO_CODORNIZ,
	T_HUEVO_POCHE,
	T_HUEVO_RELOJ
};

class Evento: public Mensaje {
public:
	/**
	 * Constructor con parámetro por default que inicializa en un evento
	 * indefinido.
	 * @param evento Tipo de evento que se desea crear.
	 */
	explicit Evento(TipoEvento evento = E_INDEFINIDO);

	/**
	 * Constructor que inicializa el evento en modo pedido de lanzamiento de
	 * disparo.
	 * @param tDisparo Tipo de disparo que se quiere realizar.
	 * @param puntoADisparar Punto2D que establece la ubicación hacia donde se
	 * quiere disparar.
	 */
	Evento(TipoDisparo tDisparo, Punto2D puntoADisparar);

	/**
	 * Constructor que inicializa el evento en modo lanzamiento de pajaro.
	 * @param tPajaro Tipo de pajaro que se desea lanzar.
	 * @param puntoInicial Punto2D que establece la posicion desde el cual
	 * comenzar el lanzamiento.
	 * @param velInicial Velocidad2D que establece la velocidad desde la cual
	 * comenzar el lanzamiento.
	 */
	Evento(TipoPajaro tPajaro, Punto2D puntoInicial, Velocidad2D velInicial);

	/**
	 * Constructor que inicializa el evento en modo lanzamiento de disparo.
	 * @param tDisparo Tipo de disparo que se desea lanzar.
	 * @param puntoInicial Punto2D que establece la posicion desde el cual
	 * comenzar el lanzamiento.
	 * @param velInicial Velocidad2D que establece la velocidad desde la cual
	 * comenzar el lanzamiento.
	 */
	Evento(TipoDisparo tDisparo, Punto2D puntoInicial, Velocidad2D velInicial);

	/**
	 * Constructor que inicializa el evento mediante una cadena.
	 * @param eventoSerealizado Cadena de caracteres que contiene el evento
	 * serealizado.
	 */
	Evento(std::string eventoSerealizado);

	/**
	 * Destructor.
	 */
	virtual ~Evento();

	/**
	 * @brief serializa la informacion de la clase a cadena de char.
	 * @return cadena de char serializados exprasados como un string.
	 */
	std::string serealizar() const;

	/**
	 * @brief deserializa la informacion de la clase a partir de una
	 * cadena de char.
	 * @param cadena de char a deserializar.
	 */
	void deserealizar(const std::string& mensaje);

	TipoEvento getTipoEvento() const;

	TipoPajaro getTipoPajaro() const;

	TipoDisparo getTipoDisparo() const;

	Punto2D getPunto() const;

	Velocidad2D getVelocidad() const;

private:

	std::string serializarDisparo() const;

	std::string serializarPajaro() const;

	std::string serializarPunto() const;

	std::string serializarVelocidad() const;

	void decodificarDisparo(const std::string& mensaje);

	void decodificarPajaro(const std::string& mensaje);

	void decodificarPunto(const std::string& mensaje);

	void decodificarVelocidad(const std::string& mensaje);

	std::string floatToString(const float valor) const;

	float stringToFloat(const std::string) const;

	// Tipo de evento que se almacena.
	TipoEvento evento;

	// Tipo de pájaro que se almacena.
	TipoPajaro pajaro;

	// Tipo de disparo que se almacena.
	TipoDisparo disparo;

	// Punto inicial de pajaro o disparo
	Punto2D punto;

	// Velocidad inicial del pajaro o disparo
	Velocidad2D velocidad;
};

#endif /* EVENTO_H_ */
