// Header Include.
#include "Suelo.h"

// Project Includes.
#include "ConstantesColisiones.h"

Suelo::Suelo(b2Body* body, float ancho, float alto) : CuerpoAbstracto(body, 100000000) {
	this->cuerpo->SetUserData(this);
	// Defino la forma del suelo y lo agrego al body
	b2PolygonShape groundBox;
	groundBox.SetAsBox(ancho / 2, alto / 2);
	// Defino las propiedades del cuerpo
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.filter.categoryBits = CATEGORY_SUELO;
	fixtureDef.filter.maskBits = MASK_SUELO;
	this->cuerpo->CreateFixture(&fixtureDef);
}

Suelo::~Suelo() { }

XMLNode* Suelo::serialize() {
	// Creo el nodo del suelo
	XMLNode* nodo = new XMLNode("Suelo");
	// TODO(eze) Implementar luego de ver como se va a implementar el suelo.
	return nodo;
}

void Suelo::hydrate(const XMLNode* nodo) {
	// No realiza nada porque se requiere el b2Body.
}

void Suelo::agregarPunto(Punto2D p) {
	// TODO Auto-generated
}

void Suelo::borrarPunto(Punto2D p) {
	// TODO Auto-generated
}
