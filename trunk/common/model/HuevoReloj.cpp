// Header Include.
#include "HuevoReloj.h"

// Project Includes.
#include "Constantes.h"

HuevoReloj::HuevoReloj(b2Body* body, unsigned int idJugador,
		Jugador* jugador, int milisegundos) :
		Disparo(body, idJugador, jugador, HR_DANIO_PAJARO, HR_DANIO_SUPERFICIE) {
	// Defino los atributos de clase
	this->danioCerdito = HR_DANIO_CERDITO;

	// Paso una referencia de este objeto al body de Box2D
	this->cuerpo->SetUserData(this);

	// Defino la forma del cuerpo
	b2CircleShape dynamicBox;
	dynamicBox.m_radius = HR_RADIO;

	// Defino las propiedades del cuerpo
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.8f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.groupIndex = GROUP_DISPARO;
	fixtureDef.filter.categoryBits = CATEGORY_DISPARO;
	fixtureDef.filter.maskBits = MASK_DISPARO;
	this->cuerpo->CreateFixture(&fixtureDef);

	// TODO completar el seteo del tiempo, falta el random
	// TODO agregar el tiempo minimo y maximo como constantes.
	tiempoExplosion = milisegundos;
}

HuevoReloj::~HuevoReloj() { }

XMLNode* HuevoReloj::serialize() {
	// Serializo la posicion del huevo
	const b2Vec2 vecPos = this->cuerpo->GetPosition();
	Punto2D p(vecPos.x, vecPos.y);
	XMLNode* pos = p.serialize();
	// Serializo la velocidad del huevo
	const b2Vec2 vecVel = this->cuerpo->GetLinearVelocity();
	Velocidad2D v(vecVel.x, vecVel.y);
	XMLNode* vel = v.serialize();
	// Creo el nodo para el huevo
	XMLNode* nodo = new XMLNode("HuevoReloj");
	// Seteo el atributo de identificador del jugador
	nodo->SetAttribute("jugadorID", this->identificador);
	// TODO(eze) falta agregar el atributo del tiempo restante.
	// Agrego el nodo del Punto2D y Velocidad2D
	nodo->LinkEndChild(pos);
	nodo->LinkEndChild(vel);
	return nodo;
}

void HuevoReloj::hydrate(const XMLNode* nodo) {
	// No realiza nada porque se requiere el b2Body.
}

void HuevoReloj::vivir(int milisegundos) {
	this->tiempoExplosion -= milisegundos;

	if (this->tiempoExplosion <= 0) {
		this->explotar();
	}
}

void HuevoReloj::explotar() {
	this->aumentarTamanio();
	this->matar();
}

void HuevoReloj::aumentarTamanio() {
}
