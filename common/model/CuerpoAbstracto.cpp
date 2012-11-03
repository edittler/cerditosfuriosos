// Header Include.
#include "CuerpoAbstracto.h"

#include <cstdio>  // TODO PROVISORIO, BORRAR

CuerpoAbstracto::CuerpoAbstracto() {
	// TODO Auto-generated constructor stub
}

CuerpoAbstracto::~CuerpoAbstracto() {
	// TODO Auto-generated destructor stub
}

bool CuerpoAbstracto::estaVivo() const {
	if (this->vida <= 0)
		return false;
	return true;
}

void CuerpoAbstracto::daniar(float danio) {
	this->vida -= danio;
	// Si la vida resulta negativa, aviso al observador que el cuerpo se murio.
	if (this->observador != 0) {
		this->observador->seMurio();
	}
}

void CuerpoAbstracto::matar() {
	this->vida = 0;
	// Como se mató al cuerpo, aviso al observador.
	if (this->observador != 0) {
		this->observador->seMurio();
	}
}

void CuerpoAbstracto::notificarPosicionAObservador() {
	// Si el observador en no nulo, le envio la posicion.
	if (this->observador != 0) {
		b2Vec2 vec = this->cuerpo->GetPosition();
		Punto2D p;
		p.x = vec.x;
		p.y = vec.y;
		this->observador->actualizarPosicion(p);
	}
}

void CuerpoAbstracto::printPosition() const {
	b2Vec2 position = this->cuerpo->GetPosition();
	printf("Cuerpo: x=%4.2f y=%4.2f  ", position.x, position.y);
}
