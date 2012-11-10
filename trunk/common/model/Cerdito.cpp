// Header Include.
#include "Cerdito.h"

// Project Includes.
#include "Constantes.h"

Cerdito::Cerdito(b2Body* body, Catapulta* catapulta) :
				CuerpoAbstracto (body, CE_VIDA)
{
	// Defino los atributos de la clase Cerdito
	this->catapulta = catapulta;
	// Paso una referencia de este objeto al body de Box2D
	this->cuerpo->SetUserData(this);
	// Defino la forma del cuerpo
	b2CircleShape dynamicBox;
	dynamicBox.m_radius = CE_RADIO;
	// Defino las propiedades del cuerpo
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 10.8f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.categoryBits = CATEGORY_CERDITO;
	fixtureDef.filter.maskBits = MASK_CERDITO;
	this->cuerpo->CreateFixture(&fixtureDef);
}

Cerdito::~Cerdito() {
	delete this->catapulta;
}

XMLNode* Cerdito::serialize() {
	// Serializo la posicion del cerdito
	const b2Vec2 vec = this->cuerpo->GetPosition();
	Punto2D p(vec.x, vec.y);
	XMLNode* punto = p.serialize();
	// Obtengo el nodo de la catapulta.
	XMLNode* catapulta = this->catapulta->serialize();
	// Creo el nodo para el cerdito
	XMLNode* nodo = new XMLNode("Catapulta");
	// Agrego el nodo del Punto2D
	nodo->LinkEndChild(punto);
	nodo->LinkEndChild(catapulta);
	return nodo;
}

void Cerdito::hydrate(const XMLNode* nodo) {
	/* No realiza nada porque el objeto se construye con todos los atributos
	 * necesarios.
	 * Además, tampoco hay posibilidades de hidratarse a partir de un nodo XML
	 * porque no hay manera de obtener el body de Box2D sin obtenerlo del
	 * World de Box2D.
	 */
}

const Catapulta* Cerdito::getCatapulta() {
	return this->catapulta;
}
