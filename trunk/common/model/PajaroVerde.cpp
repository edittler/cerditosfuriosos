// Header Include.
#include "PajaroVerde.h"

// Project Includes.
#include "Constantes.h"

PajaroVerde::PajaroVerde(b2Body* body) :
		Pajaro(body, PV_VIDA, PV_DANIO_CERDITO, PV_DANIO_SUPERFICIE) {
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

PajaroVerde::~PajaroVerde() { }

XMLNode* PajaroVerde::serialize() {
	// Serializo la posicion del pajaro
	const b2Vec2 vecPos = this->cuerpo->GetPosition();
	Punto2D p(vecPos.x, vecPos.y);
	XMLNode* pos = p.serialize();
	// Serializo la velocidad del pajaro
	const b2Vec2 vecVel = this->cuerpo->GetLinearVelocity();
	Velocidad2D v(vecVel.x, vecVel.y);
	XMLNode* vel = v.serialize();
	// Creo el nodo para el pajaro
	XMLNode* nodo = new XMLNode("PajaroVerde");
	// Agrego el nodo del Punto2D y Velocidad2D
	nodo->LinkEndChild(pos);
	nodo->LinkEndChild(vel);
	return nodo;
}

void PajaroVerde::hydrate(const XMLNode* nodo) {
	// No realiza nada porque se requiere el b2Body.
}
