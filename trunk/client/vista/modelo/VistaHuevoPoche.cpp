#include "VistaHuevoPoche.h"
#include "ConstantesVistaModelo.h"

// Forward Includes.
#include "VistaEscenario.h"

VistaHuevoPoche::VistaHuevoPoche(VistaEscenario* escenario, HuevoPoche* huevo) :
	VistaCuerpo(escenario, huevo, RUTA_HUEVO_POCHE) {
	// Registro el observador en el modelo.
	huevo->registrarObservador(this);
}

VistaHuevoPoche::~VistaHuevoPoche() {
	// Elimino el observador del modelo
	this->cuerpo->eliminarObservador(this);
}

