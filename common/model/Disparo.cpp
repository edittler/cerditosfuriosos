// Header Include.
#include "Disparo.h"

Disparo::Disparo() { }

Disparo::~Disparo() { }

void Disparo::chocarCon(Superficie* superficie) {
	superficie->daniar(danioSuperficie);
	if (!superficie->estaVivo())
		jugador->sumarPuntos(superficie->getPuntosDestruccion());

	matar();
}

void Disparo::chocarCon(Pajaro* pajaro) {
	pajaro->daniar(danioPajaro);
	matar();
}

void Disparo::chocarCon(Cerdito* cerdito) {
	matar();
}

void Disparo::chocarCon(Monticulo* monticulo) {
	// TODO tomo el monticulo como una superficie, no estoy seguro...
	monticulo->daniar(danioSuperficie);
}

void Disparo::chocarCon(Fruta* fruta) {
	jugador->sumarPuntos(fruta->getPuntosAdquisicion());
	fruta->matar();
}
