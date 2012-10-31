// Header Include.
#include "Cereza.h"
#include "Constantes.h"

Cereza::Cereza(b2Body* body) {
	this->puntosAdquisicion = FC_PUNTOS;
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

Cereza::~Cereza() {
	// TODO Auto-generated destructor stub
}

