#include "VistaHuevoCodorniz.h"
#include "ConstantesVistaModelo.h"

// Forward Include
#include "VistaEscenario.h"

VistaHuevoCodorniz::VistaHuevoCodorniz(VistaEscenario* escenario, HuevoCodorniz* huevo) :
		VistaCuerpo(escenario, huevo, RUTA_HUEVO_CODORNIZ) {
	huevo->registrarObservador(this);
}

VistaHuevoCodorniz::~VistaHuevoCodorniz() {
	this->cuerpo->eliminarObservador(this);
}

