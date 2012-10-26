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
	HuevoBlanco();
	virtual ~HuevoBlanco();

	/**************************
	 * DOUBLE DISPATCH METODS *
	 **************************/
	// SUPERFICIES
	void chocarCon(const CajaMadera* caja);

	// PAJAROS
	void chocarCon(const PajaroRojo* pajaro);

	// DISPAROS
	void chocarCon(const HuevoBlanco* huevo);
};

#endif /* HUEVOBLANCO_H_ */
