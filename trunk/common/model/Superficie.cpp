/*
 * Superficie.cpp
 *
 *  Created on: 24/10/2012
 *      Author: ezequiel
 */

// Header Include.
#include "Superficie.h"

Superficie::Superficie() {
	// TODO Auto-generated constructor stub

}

Superficie::~Superficie() {
	// TODO Auto-generated destructor stub
}

void Superficie::daniar(float danio) {
	this->vida -= danio;
}

int Superficie::getPuntosDestruccion() const {
	return puntosDestruccion;
}
