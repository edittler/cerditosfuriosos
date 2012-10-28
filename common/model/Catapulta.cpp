// Header Include.
#include "Catapulta.h"

// Projet Includes.
#include "Constantes.h"

Catapulta::Catapulta(b2Body* body) {
	// Defino los atributos de clase
	this->cuerpo = body;
	/* La vida de la catapulta es irrelevante porque no se destruye nunca, pero
	 * asigno un valor positivo distinto de 0 para considerarse un cuerpo vivo.
	 */
	this->vida = 1;
	// Paso una referencia de este objeto al body de Box2D
	this->cuerpo->SetUserData(this);
	// Defino la forma del cuerpo
	b2PolygonShape staticBox;
	staticBox.SetAsBox(CAT_MEDIO_ANCHO, CAT_MEDIO_ANCHO);
	// Defino las propiedades del cuerpo
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &staticBox;
	fixtureDef.density = 10.0f;
	fixtureDef.friction = 0.3f;
	this->cuerpo->CreateFixture(&fixtureDef);
}

Catapulta::~Catapulta() { }
