// Header Include.
#include "Pajaro.h"

Pajaro::Pajaro() { }

Pajaro::~Pajaro() { }

void Pajaro::chocarCon(Superficie* superficie) {
	superficie->daniar(this->danioSuperficie);
}
