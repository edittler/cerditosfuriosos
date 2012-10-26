/*
 * Posicionable.cpp
 *
 *  Created on: 24/10/2012
 *      Author: ezequiel
 */
// Header Include.
#include "CuerpoAbstracto.h"

CuerpoAbstracto::CuerpoAbstracto() {
	// TODO Auto-generated constructor stub

}

CuerpoAbstracto::~CuerpoAbstracto() {
	// TODO Auto-generated destructor stub
}

bool CuerpoAbstracto::estaVivo() const {
	if (this->vida <= 0)
		return false;
	return true;
}
