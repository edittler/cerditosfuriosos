#ifndef HUEVOCODORNIZ_H_
#define HUEVOCODORNIZ_H_

// Hierarchy Include.
#include "Disparo.h"

class HuevoCodorniz: public Disparo {
public:
	/* @brief Constructor con parámetros.
	 * @param body obtenido del World de Box2D.
	 * @param identificador del jugador que lanza el huevo.
	 * @param jugador que lanza el huevo.
	 */
	HuevoCodorniz(b2Body* body, unsigned int idJugador, Jugador* jugador);

	// Destructor
	virtual ~HuevoCodorniz();
};

#endif /* HUEVOCODORNIZ_H_ */
