// Header Include.
#include "VistaCerdito.h"

// Forward Includes.
#include "VistaEscenario.h"

VistaCerdito::VistaCerdito(VistaEscenario* escenario, Punto2D posicion):
	VistaCuerpo(escenario, posicion, RUTA_CERDITO) {
	this->escenario = escenario;
}

VistaCerdito::~VistaCerdito() {}
