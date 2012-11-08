#include "VistaMonticulo.h"
#include "ConstantesVistaModelo.h"

// Forward Include
#include "VistaEscenario.h"

VistaMonticulo::VistaMonticulo(VistaEscenario* escenario, Monticulo* monticulo) :
		VistaCuerpo(escenario, monticulo, RUTA_MONTICULO_COMPLETO) {
	monticulo->registrarObservador(this);
}

VistaMonticulo::~VistaMonticulo() {
	this->cuerpo->eliminarObservador(this);
}

