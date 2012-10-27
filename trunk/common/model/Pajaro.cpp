/*
 * Pajaro.cpp
 *
 *  Created on: 25/10/2012
 *      Author: ezequiel
 */
// Header Include.
#include "Pajaro.h"

// Project Includes.
#include "Superficie.h"

Pajaro::Pajaro() {
	// TODO Auto-generated constructor stub

}

Pajaro::~Pajaro() {
	// TODO Auto-generated destructor stub
}

void Pajaro::chocarCon(Superficie* superficie) {
	superficie->daniar(this->danioSuperficie);

}

float Pajaro::getDanioCerdito() const {
	return danioCerdito;
}

float Pajaro::getDanioSuperficie() const {
	return danioSuperficie;
}
