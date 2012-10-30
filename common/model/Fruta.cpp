#include "Fruta.h"

Fruta::Fruta() {
	this->vida = 1;  // las frutas desaparecen al ser tocadas
}

Fruta::~Fruta() {
	// TODO Auto-generated destructor stub
}

int Fruta::getPuntosAdquisicion() const {
	return this->puntosAdquisicion;
}
