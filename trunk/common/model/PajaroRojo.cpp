/*
 * PajaroRojo.cpp
 *
 *  Created on: 25/10/2012
 *      Author: ezequiel
 */

// Header Include.
#include "PajaroRojo.h"

// Double Dispatch Includes.
// SUPERFICIES
#include "CajaMadera.h"
// DISPAROS
#include "HuevoBlanco.h"

PajaroRojo::PajaroRojo(b2Body* body) {
	// Defino los atributos de clase
	this->cuerpo = body;
	this->vida = 0.5;
	this->danioCerdito = 1;
	this->danioSuperficie = 0.5;
	// Paso una referencia de este objeto al body de Box2D
	this->cuerpo->SetUserData(this);
	// Defino la forma del cuerpo
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	// Defino las propiedades del cuerpo
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.8f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.33f;
	this->cuerpo->CreateFixture(&fixtureDef);
}

PajaroRojo::~PajaroRojo() {
	// TODO Auto-generated destructor stub
}

void PajaroRojo::chocarCon(const CajaMadera* caja) {
	/* Al chocar con la caja de madera, el pajaro no cambia su estado
	 * salvo rebotar. El rebote sera manejado por Box2D.
	 * El daño que le causa a la caja es calculado por ésta.
	 */
}

void PajaroRojo::chocarCon(const PajaroRojo* pajaro) {
	/* Los pajaros pueden superponerse normalmente, por lo que no realiza nada.
	 */
}

void PajaroRojo::chocarCon(const HuevoBlanco* huevo) {
	/* El huevo le genera un daño al pajaro, por lo que le resto la cantidad
	 * de daño en la vida.
	 */
	this->vida -= huevo->getDanioPajaro();
	/* Si la vida es menor o igual a 0, debo avisarle a la visa que lo elimine
	 */
	if (this->vida <= 0) {
		// TODO Implementar que la vista elimine el objeto
	}
}
