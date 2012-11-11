#ifndef HUEVOPOCHE_H_
#define HUEVOPOCHE_H_

// Hierarchy Include.
#include "Disparo.h"

class HuevoPoche: public Disparo {
public:
	/* @brief Constructor con parámetros.
	 * @param body obtenido del World de Box2D.
	 * @param identificador del jugador que lanza el huevo.
	 * @param jugador que lanza el huevo.
	 */
	HuevoPoche(b2Body* body, unsigned int idJugador, Jugador* jugador);

	// Destructor
	virtual ~HuevoPoche();
};

#endif /* HUEVOPOCHE_H_ */
