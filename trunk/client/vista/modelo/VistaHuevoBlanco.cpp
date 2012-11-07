#include "VistaHuevoBlanco.h"
#include "ConstantesVistaModelo.h"

// Forward Includes.
#include "VistaEscenario.h"

VistaHuevoBlanco::VistaHuevoBlanco(VistaEscenario* escenario, HuevoBlanco* huevo) :
	VistaCuerpo(escenario, huevo, RUTA_HUEVO_BLANCO) {
	// Registro el observador en el modelo.
	huevo->registrarObservador(this);
}

VistaHuevoBlanco::~VistaHuevoBlanco() {
	// Elimino el observador del modelo
	this->cuerpo->eliminarObservador(this);
}

