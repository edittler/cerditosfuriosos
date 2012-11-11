#ifndef HUEVORELOJ_H_
#define HUEVORELOJ_H_

// Hierarchy Include.
#include "Disparo.h"

class HuevoReloj: public Disparo {
public:
	/* @brief Constructor con parámetros.
	 * @param body obtenido del World de Box2D.
	 * @param identificador del jugador que lanza el huevo.
	 * @param jugador que lanza el huevo.
	 */
	HuevoReloj(b2Body* body, unsigned int idJugador, Jugador* jugador);

	// Destructor
	virtual ~HuevoReloj();

private:
	// Metodo que hace explotar el huevo.
	bool explotar();

	// Danio que le causa el cerdito.
	float danioCerdito;

	// Tiempo que tarda en explotar
	float tiempoExplosion;
};

#endif
