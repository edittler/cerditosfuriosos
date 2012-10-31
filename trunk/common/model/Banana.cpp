// Header Include.
#include "Banana.h"
#include "Constantes.h"

Banana::Banana(b2Body* body) {
	this->puntosAdquisicion = FB_PUNTOS;
	this->cuerpo = body;
	// Paso una referencia de este objeto al body de Box2D
	this->cuerpo->SetUserData(this);
	// Defino la forma del cuerpo
	b2CircleShape staticBox;
	staticBox.m_radius = F_RADIO;
	// Defino las propiedades del cuerpo
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &staticBox;
	fixtureDef.filter.categoryBits = CATEGORY_FRUTA;
	fixtureDef.filter.maskBits = MASK_FRUTA;
	this->cuerpo->CreateFixture(&fixtureDef);
}

Banana::~Banana() {
	// TODO Auto-generated destructor stub
}

