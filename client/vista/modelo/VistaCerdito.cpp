// Header Include.
#include "VistaCerdito.h"

// Project Includes.
#include "ConstantesVistaModelo.h"

// Forward Includes.
#include "VistaEscenario.h"

VistaCerdito::VistaCerdito(VistaEscenario* escenario, Cerdito* cerdito):
	VistaCuerpo(escenario, cerdito, RUTA_CERDITO)
{
	// FIXME el registro y la eliminacion del observador podria refactorizarse
	// y pasare al constructor y destructor de VistaCuerpo. Idem para todas las vistas.

	// Registro el observador en el modelo.
	cerdito->registrarObservador(this);
}

VistaCerdito::~VistaCerdito() {
	// Elimino el observador del modelo
	this->cuerpo->eliminarObservador(this);
}
