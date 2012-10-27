/*
 * PajaroRojo.cpp
 *
 *  Created on: 25/10/2012
 *      Author: ezequiel
 */

// Header Include.
#include "PajaroRojo.h"
#include "Constantes.h"

// Double Dispatch Includes.
// SUPERFICIES
#include "CajaMadera.h"
// DISPAROS
#include "HuevoBlanco.h"

PajaroRojo::PajaroRojo(b2Body* body) {
	// Defino los atributos de clase
	this->cuerpo = body;
	this->vida = PR_VIDA;
	this->danioCerdito = PR_DANIO_CERDITO;
	this->danioSuperficie = PR_DANIO_SUPERFICIE;
	// Paso una referencia de este objeto al body de Box2D
	this->cuerpo->SetUserData(this);
	// Defino la forma del cuerpo
	b2CircleShape dynamicBox;
	dynamicBox.m_radius = PR_RADIO;
	// Defino las propiedades del cuerpo
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.8f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = PR_RESTITUCION;
	fixtureDef.filter.groupIndex = GROUP_PAJARO;
	fixtureDef.filter.categoryBits = CATEGORY_PAJARO;
	fixtureDef.filter.maskBits = MASK_PAJARO;
	this->cuerpo->CreateFixture(&fixtureDef);
}

PajaroRojo::~PajaroRojo() {
	// TODO Auto-generated destructor stub
}
