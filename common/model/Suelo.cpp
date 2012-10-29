#include "Suelo.h"

Suelo::Suelo(b2Body* body) {
	// TODO Auto-generated constructor stub
	this->vida = 1;
	this->cuerpo = body;
	this->cuerpo->SetUserData(this);
	// Defino la forma del suelo y lo agrego al body
	b2PolygonShape groundBox;
	groundBox.SetAsBox(100.0f, 10.0f);
	this->cuerpo->CreateFixture(&groundBox, 0.0f);
}

Suelo::~Suelo() {
	// TODO Auto-generated destructor stub
}

void Suelo::agregarPunto(Punto2D p) {
	// TODO Auto-generated
}

void Suelo::borrarPunto(Punto2D p) {
	// TODO Auto-generated
}
