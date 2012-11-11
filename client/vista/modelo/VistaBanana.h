#ifndef VISTABANANA_H_
#define VISTABANANA_H_

#include "VistaCuerpo.h"
#include "Banana.h"

class VistaBanana: public VistaCuerpo {
public:
	/**
	 * Constructor.
	 * @param escenario puntero a la vista a la que le notificaremos cambios
	 * @param banana referencia al objeto observado.
	 */
	VistaBanana(VistaEscenario* escenario, Banana* banana);
	virtual ~VistaBanana();
};

#endif
