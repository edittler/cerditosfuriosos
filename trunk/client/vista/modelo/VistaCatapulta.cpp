// Header Include.
#include "VistaCatapulta.h"

// Project Includes.
#include "ConstantesVistaModelo.h"

// Forward Includes.
#include "VistaEscenario.h"

VistaCatapulta::VistaCatapulta(VistaEscenario* escenario, Catapulta* catapulta):
	VistaCuerpo(escenario, catapulta, RUTA_CATAPULTA)
{
	// FIXME el registro y la eliminacion del observador podria refactorizarse
	// y pasare al constructor y destructor de VistaCuerpo. Idem para todas las vistas.

	// Registro el observador en el modelo.
	catapulta->registrarObservador(this);
}

VistaCatapulta::~VistaCatapulta() {
	// Elimino el observador del modelo
	this->cuerpo->eliminarObservador(this);
}
