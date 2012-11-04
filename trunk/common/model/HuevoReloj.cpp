// Header Include.
#include "HuevoReloj.h"
#include "Constantes.h"

HuevoReloj::HuevoReloj(b2Body* body) {
	// Defino los atributos de clase
	this->cuerpo = body;
	this->vida = 1;
	this->jugador = jugador;
	this->danioPajaro = HR_DANIO_PAJARO;
	this->danioSuperficie = HR_DANIO_SUPERFICIE;
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

	// TODO completar tiempo
	tiempoExplosion = 6.0f;
}

HuevoReloj::~HuevoReloj() {
	// TODO Auto-generated destructor stub
}

bool HuevoReloj::explotar() {
	if (this->tiempoExplosion > 0) {
		return false;
	}

	return true;
}
