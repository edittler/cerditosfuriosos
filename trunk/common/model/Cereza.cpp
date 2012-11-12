// Header Include.
#include "Cereza.h"

// Project Includes.
#include "Constantes.h"

Cereza::Cereza(b2Body* body) : Fruta(body, FC_PUNTOS) {
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

Cereza::~Cereza() { }

XMLNode* Cereza::serialize() {
	// Serializo la posicion de la fruta
	const b2Vec2 vec = this->cuerpo->GetPosition();
	Punto2D p(vec.x, vec.y);
	XMLNode* punto = p.serialize();
	// Creo el nodo para la fruta
	XMLNode* nodo = new XMLNode("Cereza");
	// Agrego el nodo del Punto2D
	nodo->LinkEndChild(punto);
	return nodo;
}

void Cereza::hydrate(const XMLNode* nodo) {
	// No realiza nada porque se requiere el b2Body.
}
