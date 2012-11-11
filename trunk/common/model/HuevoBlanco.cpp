// Header Include.
#include "HuevoBlanco.h"

// Project Includes.
#include "Constantes.h"

HuevoBlanco::HuevoBlanco(b2Body* body, unsigned int idJugador,
		Jugador* jugador) :
		Disparo(body, idJugador, jugador, HB_DANIO_PAJARO, HB_DANIO_SUPERFICIE)
{
	// Paso una referencia de este objeto al body de Box2D
	this->cuerpo->SetUserData(this);
	// Defino la forma del cuerpo
	b2CircleShape dynamicBox;
	dynamicBox.m_radius = HB_RADIO;
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

HuevoBlanco::~HuevoBlanco() { }
