// Header Include.
#include "PajaroVerde.h"
#include "Constantes.h"

PajaroVerde::PajaroVerde(b2Body* body) {
	// Defino los atributos de clase
	this->cuerpo = body;
	this->vida = PV_VIDA;
	this->danioCerdito = PV_DANIO_CERDITO;
	this->danioSuperficie = PV_DANIO_SUPERFICIE;
	// Paso una referencia de este objeto al body de Box2D
	this->cuerpo->SetUserData(this);
	// Defino la forma del cuerpo
	b2CircleShape dynamicBox;
	dynamicBox.m_radius = PV_RADIO;
	// Defino las propiedades del cuerpo
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.8f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = PV_RESTITUCION;
	fixtureDef.filter.groupIndex = GROUP_PAJARO;
	fixtureDef.filter.categoryBits = CATEGORY_PAJARO;
	fixtureDef.filter.maskBits = MASK_PAJARO;
	this->cuerpo->CreateFixture(&fixtureDef);
}

PajaroVerde::~PajaroVerde() {
	// TODO Auto-generated destructor stub
}

