// Header Include.
#include "PajaroAzul.h"
#include "Constantes.h"

PajaroAzul::PajaroAzul(b2Body* body) {
	this->cuerpo = body;
	this->vida = PA_VIDA;
	this->danioCerdito = PA_DANIO_CERDITO;
	this->danioSuperficie = PA_DANIO_SUPERFICIE;
	// Paso una referencia de este objeto al body de Box2D
	this->cuerpo->SetUserData(this);
	// Defino la forma del cuerpo
	b2CircleShape dynamicBox;
	dynamicBox.m_radius = PA_RADIO;
	// Defino las propiedades del cuerpo
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.8f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = PA_RESTITUCION;
	fixtureDef.filter.groupIndex = GROUP_PAJARO;
	fixtureDef.filter.categoryBits = CATEGORY_PAJARO;
	fixtureDef.filter.maskBits = MASK_PAJARO;
	this->cuerpo->CreateFixture(&fixtureDef);
}

PajaroAzul::~PajaroAzul() {
	// TODO Auto-generated destructor stub
}

