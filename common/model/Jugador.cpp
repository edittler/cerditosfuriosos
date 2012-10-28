// Header Include.
#include "Jugador.h"

Jugador::Jugador(Cerdito* cerdito) {
	this->cerdito = cerdito;
}

Jugador::~Jugador() { }

void Jugador::sumarPuntos(int puntos) {
	this->puntaje.sumarPuntos(puntos);
}
