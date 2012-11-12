// Header Include.
#include "Superficie.h"

Superficie::Superficie(b2Body* body, float vida, int puntosDestruccion) :
		CuerpoAbstracto(body, vida) {
	this->puntosDestruccion = puntosDestruccion;
}

Superficie::~Superficie() { }

int Superficie::getPuntosDestruccion() const {
	return puntosDestruccion;
}
