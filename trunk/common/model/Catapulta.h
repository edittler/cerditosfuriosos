#ifndef CATAPULTA_H_
#define CATAPULTA_H_

// Hierarchy Include.
#include "CuerpoAbstracto.h"

/* Clase Catapulta, abstraccion de la catapulta que aparece en el juego
 * Cerditos Furiosos.
 */
class Catapulta: public CuerpoAbstracto {
public:
	explicit Catapulta(b2Body* body);
	virtual ~Catapulta();
};

#endif /* CATAPULTA_H_ */
