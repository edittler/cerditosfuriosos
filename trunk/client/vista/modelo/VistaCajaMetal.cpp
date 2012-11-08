#include "VistaCajaMetal.h"
#include "ConstantesVistaModelo.h"

// Forward Include
#include "VistaEscenario.h"

VistaCajaMetal::VistaCajaMetal(VistaEscenario* escenario, CajaMetal* caja) :
		VistaCuerpo(escenario, caja, RUTA_CAJA_METAL) {
	caja->registrarObservador(this);
}

VistaCajaMetal::~VistaCajaMetal() {
	this->cuerpo->eliminarObservador(this);
}

