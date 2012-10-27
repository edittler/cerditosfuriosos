/*
 * CajaMadera.h
 *
 *  Created on: 24/10/2012
 *      Author: ezequiel
 */

#ifndef CAJAMADERA_H_
#define CAJAMADERA_H_

// Hierarchy Include.
#include "Superficie.h"

class CajaMadera: public Superficie {
public:
	explicit CajaMadera(b2Body* body);
	virtual ~CajaMadera();
};

#endif /* CAJAMADERA_H_ */
