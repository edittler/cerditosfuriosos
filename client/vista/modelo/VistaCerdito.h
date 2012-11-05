#ifndef _VISTA_CERDITO_H_
#define _VISTA_CERDITO_H_

// Hierarchy Include.
#include "VistaCuerpo.h"

#define RUTA_CERDITO "imagenes/CerditoFeliz.png"

class VistaCerdito : public VistaCuerpo {
public:

	/**
	 * Constructor.
	 * @param posicion punto de referencia del cuerpo en el escenario
	 * @param escenario puntero a la vista a la que le notificaremos cambios
	 */
	VistaCerdito(VistaEscenario* escenario, Punto2D posicion,);

	/**
	 * Destructor.
	 */
	virtual ~VistaCerdito();
};

#endif
