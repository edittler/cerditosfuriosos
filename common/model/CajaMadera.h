/*
 * CajaMadera.h
 *
 *  Created on: 24/10/2012
 *      Author: ezequiel
 */

#ifndef CAJAMADERA_H_
#define CAJAMADERA_H_

#include "Superficie.h"

class CajaMadera: public Superficie {
public:
	explicit CajaMadera(b2Body* body);
	virtual ~CajaMadera();

	/**************************
	 * DOUBLE DISPATCH METODS *
	 **************************/
	// SUPERFICIES
	void chocarCon(const CajaMadera* caja);
	// PAJAROS
	void chocarCon(const PajaroRojo* pajaro);
};

#endif /* CAJAMADERA_H_ */
