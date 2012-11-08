#include "VistaCajaVidrio.h"
#include "ConstantesVistaModelo.h"

// Forward Includes.
#include "VistaEscenario.h"

VistaCajaVidrio::VistaCajaVidrio(VistaEscenario* escenario, CajaVidrio* caja) :
		VistaCuerpo(escenario, caja, RUTA_CAJA_VIDRIO) {
	caja->registrarObservador(this);
}

VistaCajaVidrio::~VistaCajaVidrio() {
	this->cuerpo->eliminarObservador(this);
}

