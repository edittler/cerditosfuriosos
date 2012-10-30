// Header Include.
#include "Disparo.h"

Disparo::Disparo() { }

Disparo::~Disparo() { }

void Disparo::chocarCon(Fruta* fruta) {
	jugador->sumarPuntos(fruta->getPuntosAdquisicion());
	fruta->matar();
}
