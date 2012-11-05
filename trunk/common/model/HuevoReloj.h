#ifndef HUEVORELOJ_H_
#define HUEVORELOJ_H_

// Hierarchy Include.
#include "Disparo.h"

class HuevoReloj: public Disparo {
private:
	float danioCerdito;
	float tiempoExplosion;

	bool explotar();
public:
	HuevoReloj(b2Body* body, Jugador* jugador);
	virtual ~HuevoReloj();
};

#endif
