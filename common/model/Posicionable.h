/*
 * Posicionable.h
 *
 *  Created on: 24/10/2012
 *      Author: ezequiel
 */

#ifndef POSICIONABLE_H_
#define POSICIONABLE_H_

#include "Box2D/Box2D.h"

class Posicionable {
protected:
	b2Body* body;  // Cuerpo de Box2D que se encapsula

public:
	Posicionable();
	virtual ~Posicionable();
};

#endif /* POSICIONABLE_H_ */
