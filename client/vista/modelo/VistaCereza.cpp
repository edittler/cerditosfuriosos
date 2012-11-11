#include "VistaCereza.h"
#include "ConstantesVistaModelo.h"

// Forward Include
#include "VistaEscenario.h"

VistaCereza::VistaCereza(VistaEscenario* escenario, Cereza* cereza) :
		VistaCuerpo(escenario, cereza, RUTA_CEREZA) {
	cereza->registrarObservador(this);
}

VistaCereza::~VistaCereza() {
	this->cuerpo->eliminarObservador(this);
}

