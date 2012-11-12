// Header Include.
#include "Fruta.h"

// Project Includes.
#include "Constantes.h"

Fruta::Fruta(b2Body* body, int puntosAdquisicion) :
		CuerpoAbstracto(body, F_VIDA) {
	this->puntosAdquisicion = puntosAdquisicion;
}

Fruta::~Fruta() { }

int Fruta::getPuntosAdquisicion() const {
	return this->puntosAdquisicion;
}
