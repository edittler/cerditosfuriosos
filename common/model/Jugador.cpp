// Header Include.
#include "Jugador.h"

Jugador::Jugador(Cerdito* cerdito) {
	this->cerdito = cerdito;
}

Jugador::~Jugador() {
	delete this->cerdito;
}

void Jugador::sumarPuntos(int puntos) {
	this->puntaje.sumarPuntos(puntos);
}

bool Jugador::perdio() {
	return !cerdito->estaVivo();
}

Cerdito* Jugador::getCerdito() {
	return this->cerdito;
}
