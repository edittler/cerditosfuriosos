// Header Include.
#include "HuevoPoche.h"

// Project Includes.
#include "Constantes.h"

HuevoPoche::HuevoPoche(b2Body* body, unsigned int idJugador,
		Jugador* jugador) :
		Disparo(body, idJugador, jugador, HP_DANIO_PAJARO, HP_DANIO_SUPERFICIE) {
	// Paso una referencia de este objeto al body de Box2D
	this->cuerpo->SetUserData(this);
	// Defino la forma del cuerpo
	b2CircleShape dynamicBox;
	dynamicBox.m_radius = HP_RADIO;
	// Defino las propiedades del cuerpo
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.8f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.groupIndex = GROUP_DISPARO;
	fixtureDef.filter.categoryBits = CATEGORY_DISPARO;
	fixtureDef.filter.maskBits = MASK_DISPARO;
	this->cuerpo->CreateFixture(&fixtureDef);
}

HuevoPoche::~HuevoPoche() { }

XMLNode* HuevoPoche::serialize() {
	// Serializo la posicion del huevo
	const b2Vec2 vecPos = this->cuerpo->GetPosition();
	Punto2D p(vecPos.x, vecPos.y);
	XMLNode* pos = p.serialize();
	// Serializo la velocidad del huevo
	const b2Vec2 vecVel = this->cuerpo->GetLinearVelocity();
	Velocidad2D v(vecVel.x, vecVel.y);
	XMLNode* vel = v.serialize();
	// Creo el nodo para el huevo
	XMLNode* nodo = new XMLNode("HuevoPoche");
	// Seteo el atributo de identificador del jugador
	nodo->SetAttribute("jugadorID", this->identificador);
	// Agrego el nodo del Punto2D y Velocidad2D
	nodo->LinkEndChild(pos);
	nodo->LinkEndChild(vel);
	return nodo;
}

void HuevoPoche::hydrate(const XMLNode* nodo) {
	// No realiza nada porque se requiere el b2Body.
}
