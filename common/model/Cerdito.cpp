// Header Include.
#include "Cerdito.h"

// Project Includes.
#include "Constantes.h"

Cerdito::Cerdito(b2Body* body, Catapulta* catapulta) {
	// Defino los atributos de clase
	this->cuerpo = body;
	this->vida = CE_VIDA;
	this->catapulta = catapulta;
	// Paso una referencia de este objeto al body de Box2D
	this->cuerpo->SetUserData(this);
	// Defino la forma del cuerpo
	b2CircleShape dynamicBox;
	dynamicBox.m_radius = CE_RADIO;
	// Defino las propiedades del cuerpo
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 10.8f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.categoryBits = CATEGORY_CERDITO;
	fixtureDef.filter.maskBits = MASK_CERDITO;
	this->cuerpo->CreateFixture(&fixtureDef);
}

Cerdito::~Cerdito() {
	delete this->catapulta;
}
