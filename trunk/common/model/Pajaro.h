/*
 * Pajaro.h
 *
 *  Created on: 25/10/2012
 *      Author: ezequiel
 */

#ifndef PAJARO_H_
#define PAJARO_H_

#include "CuerpoAbstracto.h"

class Pajaro: public CuerpoAbstracto {
protected:
	float danioCerdito;
	float danioSuperficie;

public:
	Pajaro();
	virtual ~Pajaro();

	float getDanioCerdito() const;
	float getDanioSuperficie() const;
};

#endif /* PAJARO_H_ */
