#ifndef HUEVOBLANCO_H_
#define HUEVOBLANCO_H_

#include "Disparo.h"

/* @class HuevoBlanco
 * Un tipo particular de disparo que se usa en el juego Cerditos Furiosos.
 */
class HuevoBlanco: public Disparo {
public:
	explicit HuevoBlanco(b2Body* body, Jugador* jugador);
	virtual ~HuevoBlanco();

	virtual void chocarCon(Superficie* superficie);
	virtual void chocarCon(Pajaro* pajaro);
	virtual void chocarCon(Cerdito* cerdito);
};

#endif /* HUEVOBLANCO_H_ */
