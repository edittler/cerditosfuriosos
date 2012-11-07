// Header Include.
#include "VistaCerdito.h"

// Project Includes.
#include "ConstantesVistaModelo.h"

// Forward Includes.
#include "VistaEscenario.h"

VistaCerdito::VistaCerdito(VistaEscenario* escenario, Cerdito* cerdito):
	VistaCuerpo(escenario, cerdito, RUTA_CERDITO)
{
	// Registro el observador en el modelo.
	cerdito->registrarObservador(this);
}

VistaCerdito::~VistaCerdito() {
	// Elimino el observador del modelo
	this->cuerpo->eliminarObservador(this);
}
