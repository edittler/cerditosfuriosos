/*
 * CajaMadera.cpp
 *
 *  Created on: 24/10/2012
 *      Author: ezequiel
 */

#include "CajaMadera.h"

CajaMadera::CajaMadera(b2Body* body) {
	this->vida = 1;  // Seteo la vida del cuerpo
	this->cuerpo = body;
	// Paso una referencia de este objeto al body de Box2D
	this->cuerpo->SetUserData(this);
}

CajaMadera::~CajaMadera() {
	// TODO Auto-generated destructor stub
}

void CajaMadera::chocarCon(const CajaMadera* caja) {
	// No es un caso que vaya a ocurrir, no realizo nada
}

void CajaMadera::chocarCon(const PajaroRojo* pajaro) {
	/* Solicito el danio a superficies al pajaro rojo y le resto dicha cantidad
	 * en la vida de la caja.
	 */
	this->vida -= pajaro->getDanioSuperficie();
	/* Si la vida de la caja es menor o igual a 0, debo avisarle al escenario
	 * que la elimine de la escena.
	 */
	/* TODO Implementar un patrón observador para que la caja le pueda avisar
	 * al escenario que debe eliminar este objeto.
	 */
}
