#ifndef VISTAMONTICULO_H_
#define VISTAMONTICULO_H_

#include "VistaCuerpo.h"
#include "Monticulo.h"

class VistaMonticulo: public VistaCuerpo {
public:
	/**
	 * Constructor.
	 * @param escenario puntero a la vista a la que le notificaremos cambios
	 * @param Monticulo referencia al objeto observado.
	 */
	VistaMonticulo(VistaEscenario* escenario, Monticulo* monticulo);
	virtual ~VistaMonticulo();
};

#endif /* VISTAMONTICULO_H_ */
