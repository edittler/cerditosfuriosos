#include "VistaManzana.h"
#include "ConstantesVistaModelo.h"

// Forward Include
#include "VistaEscenario.h"

VistaManzana::VistaManzana(VistaEscenario* escenario, Manzana* manzana) :
		VistaCuerpo(escenario, manzana, RUTA_MANZANA) {
	manzana->registrarObservador(this);
}

VistaManzana::~VistaManzana() {
	this->cuerpo->eliminarObservador(this);
}

