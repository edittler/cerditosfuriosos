/* Implementacion  del administrador de puntaje
 */

// Header Include
#include "Puntaje.h"

Puntaje::Puntaje() { }

Puntaje::~Puntaje() { }

void Puntaje::sumarPuntos(int puntos) {
	this->puntos += puntos;
}

int Puntaje::getPuntos() const {
	return this->puntos;
}
