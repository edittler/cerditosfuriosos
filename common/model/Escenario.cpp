/*
 * Escenario.cpp
 *
 *  Created on: 24/10/2012
 *      Author: ezequiel
 */

// Project Includes
#include "Escenario.h"
#include "CajaMadera.h"

Escenario::Escenario() {
	b2Vec2 gravity(0.0f, -10.0f);  // Vector que indica la gravedad
	this->escenario = new b2World(gravity);

}

Escenario::~Escenario() {
	delete this->escenario;
}

XMLNode Escenario::serialize() {
	return 0;
}

/* A partir de un nodo XML se establece el escenario
 * @param recibe el nodo XML que contiene los datos del escenario
 */
void Escenario::hydrate(const XMLNode& nodo) {

}

void Escenario::agregarCajaMadera(const unsigned int posX,
		const unsigned int posY) {
	b2BodyDef bodyDef;  // Definicion del cuerpo.
	bodyDef.position.Set((float32) posX, (float32) posY);  // Seteo  la posicion.
	bodyDef.type = b2_staticBody;  // Indico que el objeto va a ser estatico.
	b2Body* body = this->escenario->CreateBody(&bodyDef);

	Posicionable* cajaMadera = new CajaMadera(body);
	delete cajaMadera;
}
