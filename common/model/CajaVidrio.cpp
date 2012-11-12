// Header Include.
#include "CajaVidrio.h"

// Project Includes.
#include "Constantes.h"

CajaVidrio::CajaVidrio(b2Body* body) :
		Superficie(body, CV_VIDA, CV_PUNTOS) {
	// Paso una referencia de este objeto al body de Box2D
	this->cuerpo->SetUserData(this);
	// Defino la forma del cuerpo
	b2PolygonShape staticBox;
	staticBox.SetAsBox(CAJA_MEDIO_ANCHO, CAJA_MEDIO_ANCHO);
	// Defino las propiedades del cuerpo
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &staticBox;
	fixtureDef.density = 0.8f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.categoryBits = CATEGORY_SUPERFICIE;
	fixtureDef.filter.maskBits = MASK_SUPERFICIE;
	this->cuerpo->CreateFixture(&fixtureDef);
}

CajaVidrio::~CajaVidrio() { }

XMLNode* CajaVidrio::serialize() {
	// Serializo la posicion de la caja
	const b2Vec2 vec = this->cuerpo->GetPosition();
	Punto2D p(vec.x, vec.y);
	XMLNode* punto = p.serialize();
	// Creo el nodo para la caja
	XMLNode* nodo = new XMLNode("CajaVidrio");
	// Agrego el nodo del Punto2D
	nodo->LinkEndChild(punto);
	return nodo;
}

void CajaVidrio::hydrate(const XMLNode* nodo) {
	// No realiza nada porque se requiere el b2Body.
}
