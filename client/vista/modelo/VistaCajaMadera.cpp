#include "VistaCajaMadera.h"
#include "ConstantesVistaModelo.h"

// Forward Includes.
#include "VistaEscenario.h"

VistaCajaMadera::VistaCajaMadera(VistaEscenario* escenario, CajaMadera* caja) :
		VistaCuerpo(escenario, caja, RUTA_CAJA_MADERA) {
	// Registro el observador en el modelo.
	caja->registrarObservador(this);
}

VistaCajaMadera::~VistaCajaMadera() {
	// Elimino el observador del modelo
	this->cuerpo->eliminarObservador(this);
}

