/*
 * HuevoBlanco.h
 *
 *  Created on: 26/10/2012
 *      Author: ezequiel
 */

#ifndef HUEVOBLANCO_H_
#define HUEVOBLANCO_H_

#include "Disparo.h"

class HuevoBlanco: public Disparo {
public:
	explicit HuevoBlanco(b2Body* body);
	virtual ~HuevoBlanco();
};

#endif /* HUEVOBLANCO_H_ */
