#include "VistaBanana.h"
#include "ConstantesVistaModelo.h"

// Forward Include
#include "VistaEscenario.h"

VistaBanana::VistaBanana(VistaEscenario* escenario, Banana* banana) :
		VistaCuerpo(escenario, banana, RUTA_BANANA) {
	banana->registrarObservador(this);
}

VistaBanana::~VistaBanana() {
	this->cuerpo->eliminarObservador(this);
}

