#include "Nivel.h"

Nivel::Nivel(Escenario* escenario) {
    // TODO carga del escenario y las probabilidades para el simulador
    this->escenario = escenario;
}

Nivel::~Nivel() {
	delete escenario;
}

