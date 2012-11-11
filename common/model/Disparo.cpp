// Header Include.
#include "Disparo.h"

// Project Includes.
#include "Constantes.h"

Disparo::Disparo(b2Body* cuerpo, unsigned int idJugador, Jugador* jugador,
		float danioPajaros, float danioSuperficies) :
		CuerpoAbstracto(cuerpo, DISPARO_VIDA) {
	this->identificador = idJugador;
	this->jugador = jugador;
	this->danioPajaro = danioPajaros;
	this->danioSuperficie = danioSuperficies;
}

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
	// Dania al monticulo de huevos como si fuera una superficie.
	monticulo->daniar(danioSuperficie);
}

void Disparo::chocarCon(Fruta* fruta) {
	jugador->sumarPuntos(fruta->getPuntosAdquisicion());
	fruta->matar();
}
