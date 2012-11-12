#ifndef FRUTA_H_
#define FRUTA_H_

// Hierarchy Include.
#include "CuerpoAbstracto.h"

class Fruta: public CuerpoAbstracto {
public:
	/* @brief Constructor con parametros.
	 * @param body de Box2D asociado a la fruta.
	 * @param puntos que otorga al adquirir la fruta.
	 */
	explicit Fruta(b2Body* body, int puntosAdquisicion);

	// Destructor
	virtual ~Fruta();

	/* @brief retorna los puntos que otorga al ser adquirida
	 */
	int getPuntosAdquisicion() const;

protected:
	// Puntos que otorga al ser adquirido por un personaje.
	int puntosAdquisicion;
};

#endif /* FRUTA_H_ */
