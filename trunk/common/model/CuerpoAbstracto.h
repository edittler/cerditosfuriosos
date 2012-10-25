/*
 * Posicionable.h
 *
 *  Created on: 24/10/2012
 *      Author: ezequiel
 */

#ifndef POSICIONABLE_H_
#define POSICIONABLE_H_

// Box2D Library Includes.
#include "Box2D/Box2D.h"

// Double dispatch Includes.
// Superficies
#include "CajaMadera.h"
// Pajaros
#include "PajaroRojo.h"

class CuerpoAbstracto {
protected:
	b2Body* cuerpo;  // Cuerpo de Box2D que se encapsula
	float vida;  // Vida del cuerpo

public:
	CuerpoAbstracto();
	virtual ~CuerpoAbstracto();

	/**************************
	 * DOUBLE DISPATCH METODS *
	 **************************/
	// SUPERFICIES
	virtual void chocarCon(const CajaMadera* caja) = 0;

	// PAJAROS
	virtual void chocarCon(const PajaroRojo* pajaro) = 0;

	float getVida() const;
};

#endif /* POSICIONABLE_H_ */
