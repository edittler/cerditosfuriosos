/*
 * PajaroRojo.cpp
 *
 *  Created on: 25/10/2012
 *      Author: ezequiel
 */

#include "PajaroRojo.h"

PajaroRojo::PajaroRojo(b2Body* body) {
	this->vida = 0.5;
	this->cuerpo = body;
	// Paso una referencia de este objeto al body de Box2D
	this->cuerpo->SetUserData(this);
}

PajaroRojo::~PajaroRojo() {
	// TODO Auto-generated destructor stub
}

void PajaroRojo::chocarCon(const CajaMadera* caja) {
	/* Al chocar con la caja de madera, el pajaro no cambia su estado
	 * salvo rebotar. El rebote sera manejado por Box2D
	 */
}

void PajaroRojo::chocarCon(const PajaroRojo* pajaro) {
	/* Al chocar con otro pajaro rojo, el pajaro no cambia su estado.
	 * Los pajaros se deben poder superponer
	 */
}
