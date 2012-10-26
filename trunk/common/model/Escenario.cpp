/*
 * Escenario.cpp
 *
 *  Created on: 24/10/2012
 *      Author: ezequiel
 */

// Project Includes
#include "Escenario.h"

// Superficies Includes.
#include "CajaMadera.h"

// Pajaros Include.
#include "PajaroRojo.h"

Escenario::Escenario() {
	// Defino el tiempo de duracion de 1 tick
	this->tiempoTick = 1.0f / 50.0f;  // 20 milisegundos

	// Creo el mundo
	b2Vec2 gravity(0.0f, -10.0f);  // Vector que indica la gravedad
	this->escenario = new b2World(gravity);

	// Defino el cuerpo del suelo.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	// Creo el cuerpo del suelo.
	b2Body* groundBody = this->escenario->CreateBody(&groundBodyDef);
	// Defino la forma del suelo.
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	// Agrego las propiedades del suelo al cuerpo.
	groundBody->CreateFixture(&groundBox, 0.0f);
}

Escenario::~Escenario() {
	// Libero la memoria del escenario de Box2D
	delete this->escenario;
	// Libero la memoria de los objetos
	std::list<CuerpoAbstracto*>::iterator it;
	for(it = this->objetos.begin(); it != this->objetos.end(); ++it) {
		delete *it;
	}
}

XMLNode Escenario::serialize() {
	return 0;
}

/* A partir de un nodo XML se establece el escenario
 * @param recibe el nodo XML que contiene los datos del escenario
 */
void Escenario::hydrate(const XMLNode& nodo) {

}

void Escenario::correrTick() {
	this->escenario->Step(this->tiempoTick, 10, 8);
}

void Escenario::lanzarPajaroRojo(int posX, int posY, int velocidad,
		int angulo) {
	// Defino el cuerpo, seteo el tipo y la posicion y luego lo creo
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set((float32) posX, (float32) posY);
	b2Body* body = this->escenario->CreateBody(&bodyDef);
	// Creo el objeto CajaMadera y le paso el cuerpo de Box2D
	CuerpoAbstracto* pajaroRojo = new PajaroRojo(body);
	this->objetos.push_back(pajaroRojo);
}

void Escenario::agregarCajaMadera(const int posX, 	const int posY) {
	// Defino el cuerpo, seteo el tipo y la posicion y luego lo creo
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set((float32) posX, (float32) posY);
	b2Body* body = this->escenario->CreateBody(&bodyDef);
	// Creo el objeto CajaMadera y le paso el cuerpo de Box2D
	CuerpoAbstracto* cajaMadera = new CajaMadera(body);
	this->objetos.push_back(cajaMadera);
}

void Escenario::limpiarCuerposMuertos() {
	/* TODO Reimplementar usando la lista que contiene el escenario.
	 * Hacer que la clase Escenario sea amiga de la clase CuerpoAbstracto
	 * para que pueda acceder al body.
	 */
	b2Body* node = this->escenario->GetBodyList();
	while (node) {
		b2Body* b = node;
		node = node->GetNext();
		CuerpoAbstracto* cuerpo = (CuerpoAbstracto*)b->GetUserData();
		if (!cuerpo->estaVivo()) {
			this->escenario->DestroyBody(b);
		}
	}
}
