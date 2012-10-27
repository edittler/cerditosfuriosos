/*
 * Posicionable.h
 *
 *  Created on: 24/10/2012
 *      Author: ezequiel
 */

#ifndef CUERPOABSTRACTO_H_
#define CUERPOABSTRACTO_H_

// Box2D Library Includes.
#include "Box2D/Box2D.h"

class CuerpoAbstracto {
protected:
	b2Body* cuerpo;  // Cuerpo de Box2D que se encapsula.
	float vida;  // Vida del cuerpo.

public:
	CuerpoAbstracto();
	virtual ~CuerpoAbstracto();

	/* Retorna el estado del cuerpo
	 * @return true si el cuerpo esta vivo, false si esta muerto
	 */
	bool estaVivo() const;

	void printPosition() const; // TODO PROVISORIO, BORRAR
};

#endif /* CUERPOABSTRACTO_H_ */
