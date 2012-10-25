/*
 * Posicionable.h
 *
 *  Created on: 24/10/2012
 *      Author: ezequiel
 */

#ifndef POSICIONABLE_H_
#define POSICIONABLE_H_

#include "Box2D/Box2D.h"

class CuerpoAbstracto {
protected:
	b2Body* cuerpo;  // Cuerpo de Box2D que se encapsula
	unsigned int vida;  // Vida del cuerpo

public:
	CuerpoAbstracto();
	virtual ~CuerpoAbstracto();
};

#endif /* POSICIONABLE_H_ */
