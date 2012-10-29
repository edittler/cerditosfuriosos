// Header Include.
#include "HuevoBlanco.h"

// Project Includes.
#include "Constantes.h"

HuevoBlanco::HuevoBlanco(b2Body* body, Jugador* jugador) {
	// Defino los atributos de clase
	this->cuerpo = body;
	/* La vida de un huevo es irrelevante porque se destruye al chocar, pero
	 * asigno un valor positivo distinto de 0 para considerarse un cuerpo vivo.
	 */
	this->vida = 1;
	this->jugador = jugador;
	this->danioPajaro = HB_DANIO_PAJARO;
	this->danioSuperficie = HB_DANIO_SUPERFICIE;
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

void HuevoBlanco::chocarCon(Superficie* superficie) {
	superficie->daniar(danioSuperficie);
	if (!superficie->estaVivo())
		jugador->sumarPuntos(superficie->getPuntosDestruccion());

	matar();  // se considera al objeto como "muerto", se elimina del b2World en proxima iteracion.
}

void HuevoBlanco::chocarCon(Pajaro* pajaro) {
	pajaro->daniar(danioPajaro);
	matar();  // se considera al objeto como "muerto", se elimina del b2World en proxima iteracion.
}

void HuevoBlanco::chocarCon(Cerdito* cerdito) {
	// TODO implementar
	matar();  // se considera al objeto como "muerto", se elimina del b2World en proxima iteracion.
}
