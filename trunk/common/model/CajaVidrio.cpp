// Header Include.
#include "CajaVidrio.h"
#include "Constantes.h"

CajaVidrio::CajaVidrio(b2Body* body) {
	// Defino los atributos de clase
	this->vida = CV_VIDA;
	this->puntosDestruccion = CV_PUNTOS;
	this->cuerpo = body;
	// Paso una referencia de este objeto al body de Box2D
	this->cuerpo->SetUserData(this);
	// Defino la forma del cuerpo
	b2PolygonShape staticBox;
	staticBox.SetAsBox(CAJA_MEDIO_ANCHO, CAJA_MEDIO_ANCHO);
	// Defino las propiedades del cuerpo
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &staticBox;
	fixtureDef.density = 0.8f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.categoryBits = CATEGORY_SUPERFICIE;
	fixtureDef.filter.maskBits = MASK_SUPERFICIE;
	this->cuerpo->CreateFixture(&fixtureDef);
}

CajaVidrio::~CajaVidrio() { }
