#include "Suelo.h"

Suelo::Suelo(b2Body* body) : CuerpoAbstracto(body, 100000000) {
	this->cuerpo->SetUserData(this);
	// Defino la forma del suelo y lo agrego al body
	b2PolygonShape groundBox;
	groundBox.SetAsBox(100.0f, 10.0f);
	this->cuerpo->CreateFixture(&groundBox, 0.0f);
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
