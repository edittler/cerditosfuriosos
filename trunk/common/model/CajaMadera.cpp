/*
 * CajaMadera.cpp
 *
 *  Created on: 24/10/2012
 *      Author: ezequiel
 */
// Header Include.
#include "CajaMadera.h"
// Double Dispatch Includes.
// PAJAROS
#include "PajaroRojo.h"
// DISPAROS
#include "HuevoBlanco.h"

CajaMadera::CajaMadera(b2Body* body) {
	this->vida = 1;  // Seteo la vida del cuerpo.
	this->puntosDestruccion = 10;  // Seteo los punto que entrega al destruirse.
	this->cuerpo = body;
	// Paso una referencia de este objeto al body de Box2D
	this->cuerpo->SetUserData(this);
}

CajaMadera::~CajaMadera() {
	// TODO Auto-generated destructor stub
}

void CajaMadera::chocarCon(const CajaMadera* caja) {
	/* Como en el Box2D defini las cajas como cuerpos estaticos, este caso
	 * no va a ocurrir nunca. No realizo nada.
	 */
}

void CajaMadera::chocarCon(const PajaroRojo* pajaro) {
	/* Solicito el danio a superficies al Pajaro Rojo y le resto dicha cantidad
	 * en la vida de la caja.
	 */
	this->vida -= pajaro->getDanioSuperficie();
	/* Si la vida de la caja es menor o igual a 0, seteo el flag de vida
	 * en false y debo avisarle a la vista que lo elimine de la escena
	 */
	if (this->vida <= 0) {
		// TODO avisar a la vista que lo elimine
	}
}

void CajaMadera::chocarCon(const HuevoBlanco* huevo) {
	/* Solicito el danio a superficies al Huevo Blanco y le resto dicha cantidad
	 * en la vida de la caja.
	 */
	this->vida -= huevo->getDanioSuperficie();
	/* Si la vida de la caja es menor o igual a 0, debo otorgar los puntos
	 * correspondientes al cerdito que disparo y avisarle al escenario que
	 * elimine la caja de la escena.
	 */
	if (this->vida <= 0) {
		/* TODO agregar metodo "otorgarPuntos" a la clase Disparo
		 */
	}
}
