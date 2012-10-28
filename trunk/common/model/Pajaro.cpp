/*
 * Pajaro.cpp
 *
 *  Created on: 25/10/2012
 *      Author: ezequiel
 */
// Header Include.
#include "Pajaro.h"

Pajaro::Pajaro() { }

Pajaro::~Pajaro() { }

void Pajaro::daniar(float danio) {
	this->vida -= danio;
}

void Pajaro::chocarCon(Superficie* superficie) {
	superficie->daniar(this->danioSuperficie);
}
