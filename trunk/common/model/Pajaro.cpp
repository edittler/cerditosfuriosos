// Header Include.
#include "Pajaro.h"

Pajaro::Pajaro(b2Body* body, float vida, int danioCerditos,
		int danioSuperficies) : CuerpoAbstracto(body, vida) {
	this->danioCerdito = danioCerditos;
	this->danioSuperficie = danioSuperficies;
}

Pajaro::~Pajaro() { }

void Pajaro::chocarCon(Superficie* superficie) {
	superficie->daniar(this->danioSuperficie);
}

void Pajaro::chocarCon(Cerdito* cerdito) {
	cerdito->daniar(danioCerdito);
	matar();
}

void Pajaro::chocarCon(Fruta* fruta) {
	fruta->matar();
}

void Pajaro::chocarCon(Monticulo* monticulo) {
	monticulo->daniar(this->danioSuperficie);
	matar();
}
