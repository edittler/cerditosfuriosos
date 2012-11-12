// Header Include.
#include "Catapulta.h"

// Projet Includes.
#include "Constantes.h"

Catapulta::Catapulta(b2Body* body) : 	CuerpoAbstracto(body, CAT_VIDA) {
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

XMLNode* Catapulta::serialize() {
	// Serializo la posicion de la catapulta
	const b2Vec2 vec = this->cuerpo->GetPosition();
	Punto2D p(vec.x, vec.y);
	XMLNode* punto = p.serialize();
	// Creo el nodo para la catapulta
	XMLNode* nodo = new XMLNode("Catapulta");
	// Agrego el nodo del Punto2D
	nodo->LinkEndChild(punto);
	return nodo;
}

void Catapulta::hydrate(const XMLNode* nodo) {
	/* No realiza nada porque el objeto se construye con todos los atributos
	 * necesarios.
	 * Además, tampoco hay posibilidades de hidratarse a partir de un nodo XML
	 * porque no hay manera de obtener el body de Box2D sin obtenerlo del
	 * World de Box2D.
	 */
}
