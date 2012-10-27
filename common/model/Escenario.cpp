/*
 * Escenario.cpp
 *
 *  Created on: 24/10/2012
 *      Author: ezequiel
 */

// Project Includes
#include "Escenario.h"
#include "Colisionador.h"

// Superficies Includes.
#include "CajaMadera.h"

// Pajaros Include.
#include "PajaroRojo.h"

// Disparos Include.
#include "HuevoBlanco.h"


//#include "cmath" // FIXME borrar

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
	// Defino la forma del suelo y lo agrego al body
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Agrego el ContactListener
	this->colisionador = new Colisionador();
	this->escenario->SetContactListener(this->colisionador);
}

Escenario::~Escenario() {
	// Libero la memoria del escenario de Box2D
	delete this->escenario;
	// Libero la memoria del colisionador
	delete this->colisionador;
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
	std::list<CuerpoAbstracto*>::iterator it;
	it = objetos.begin();
	for(it = this->objetos.begin(); it != this->objetos.end(); ++it) {
		(*it)->printPosition();
	}
}

void Escenario::agregarCajaMadera(float posX, float posY) {
	// Defino el cuerpo, seteo el tipo y la posicion y luego lo creo
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set((float32) posX, (float32) posY);
	b2Body* body = this->escenario->CreateBody(&bodyDef);
	// Creo el objeto CajaMadera y le paso el cuerpo de Box2D
	CuerpoAbstracto* cajaMadera = new CajaMadera(body);
	this->objetos.push_back(cajaMadera);
}

void Escenario::lanzarPajaroRojo(float posX, float posY, float velX, float velY) {
	/* Defino el cuerpo, seteo el tipo de cuerpo, la posicion, la velocidad
	 * y luego lo creo.
	 */
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set((float32) posX, (float32) posY);
	bodyDef.linearVelocity.Set(velX, velY);
	b2Body* body = this->escenario->CreateBody(&bodyDef);
	// Creo el objeto PajaroRojo y le paso el cuerpo de Box2D
	CuerpoAbstracto* pajaroRojo = new PajaroRojo(body);
	this->objetos.push_back(pajaroRojo);
}

void Escenario::lanzarHuevoBlanco(float posX, float posY, float velX, float velY) {
	/* Defino el cuerpo, seteo el tipo de cuerpo, la posicion, la velocidad
	 * y luego lo creo.
	 */
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set((float32) posX, (float32) posY);
	bodyDef.linearVelocity.Set(velX, velY);
	b2Body* body = this->escenario->CreateBody(&bodyDef);
	// Creo el objeto HuevoBlanco y le paso el cuerpo de Box2D
	CuerpoAbstracto* huevoBlanco = new HuevoBlanco(body);
	this->objetos.push_back(huevoBlanco);
}

void Escenario::limpiarCuerposMuertos() {
	b2Body* node = this->escenario->GetBodyList();
	while (node) {
		CuerpoAbstracto* cuerpo = (CuerpoAbstracto*)node->GetUserData();
		objetos.remove(cuerpo);
		if (!cuerpo->estaVivo()) {
			this->escenario->DestroyBody(node);
		}
		node = node->GetNext();
	}
}
