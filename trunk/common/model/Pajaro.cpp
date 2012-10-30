// Header Include.
#include "Pajaro.h"

Pajaro::Pajaro() { }

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

// TODO agregar monticulo
//void Pajaro::chocarCon(Monticulo* monticulo) {
//	monticulo->restarHuevo();
//  matar();
//}
