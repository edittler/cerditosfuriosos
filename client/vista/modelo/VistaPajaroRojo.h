#ifndef VISTAPAJAROROJO_H_
#define VISTAPAJAROROJO_H_

// Hierarchy Include.
#include "VistaCuerpo.h"

// Project Includes.
#include "PajaroRojo.h"

class VistaPajaroRojo: public VistaCuerpo {
public:
	/**
	 * Constructor.
	 * @param posicion punto de referencia del cuerpo en el escenario
	 * @param escenario puntero a la vista a la que le notificaremos cambios
	 */
	VistaPajaroRojo(VistaEscenario* escenario, PajaroRojo* pajaro);

	/**
	 * Destructor.
	 */
	virtual ~VistaPajaroRojo();
};

#endif /* VISTAPAJAROROJO_H_ */
