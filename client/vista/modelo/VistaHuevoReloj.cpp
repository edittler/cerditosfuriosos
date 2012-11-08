#include "VistaHuevoReloj.h"
#include "ConstantesVistaModelo.h"

// Forward Include
#include "VistaEscenario.h"

VistaHuevoReloj::VistaHuevoReloj(VistaEscenario* escenario, HuevoReloj* huevo) :
		VistaCuerpo(escenario, huevo, RUTA_HUEVO_RELOJ) {
	huevo->registrarObservador(this);
}

VistaHuevoReloj::~VistaHuevoReloj() {
	this->cuerpo->eliminarObservador(this);
}

