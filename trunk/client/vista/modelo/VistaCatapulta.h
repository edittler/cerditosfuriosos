#ifndef _VISTA_CATAPULTA_H_
#define _VISTA_CATAPULTA_H_

// Hierarchy Include.
#include "VistaCuerpo.h"

// Project Includes.
#include "Catapulta.h"

class VistaCatapulta : public VistaCuerpo {
public:

	/**
	 * Constructor.
	 * @param posicion punto de referencia del cuerpo en el escenario
	 * @param escenario puntero a la vista a la que le notificaremos cambios
	 */
	VistaCatapulta(VistaEscenario* escenario, Catapulta* catapulta);

	/**
	 * Destructor.
	 */
	virtual ~VistaCatapulta();
};

#endif
