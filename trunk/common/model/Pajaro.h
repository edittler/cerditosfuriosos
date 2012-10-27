/*
 * Pajaro.h
 *
 *  Created on: 25/10/2012
 *      Author: ezequiel
 */

#ifndef PAJARO_H_
#define PAJARO_H_

// Hierarchy Include.
#include "CuerpoAbstracto.h"

// Forward Class Declaration
class Superficie;

class Pajaro: public CuerpoAbstracto {
protected:
	float danioCerdito;
	float danioSuperficie;

public:
	Pajaro();
	virtual ~Pajaro();

	// Metodos de colisiones
	void chocarCon(Superficie* superficie);

	float getDanioCerdito() const;
	float getDanioSuperficie() const;
};

#endif /* PAJARO_H_ */
