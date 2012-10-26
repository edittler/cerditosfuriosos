/*
 * Disparo.h
 *
 *  Created on: 26/10/2012
 *      Author: ezequiel
 */

#ifndef DISPARO_H_
#define DISPARO_H_

// Hierarchy Include.
#include "CuerpoAbstracto.h"

class Disparo: public CuerpoAbstracto {
protected:
	float danioPajaro;
	float danioSuperficie;

public:
	Disparo();
	virtual ~Disparo();

	float getDanioPajaro() const;
	float getDanioSuperficie() const;
};

#endif /* DISPARO_H_ */
