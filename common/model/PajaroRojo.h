/*
 * PajaroRojo.h
 *
 *  Created on: 25/10/2012
 *      Author: ezequiel
 */

#ifndef PAJAROROJO_H_
#define PAJAROROJO_H_

// Hierarchy Include.
#include "Pajaro.h"

class PajaroRojo: public Pajaro {
public:
	explicit PajaroRojo(b2Body* body);
	virtual ~PajaroRojo();
};

#endif /* PAJAROROJO_H_ */
