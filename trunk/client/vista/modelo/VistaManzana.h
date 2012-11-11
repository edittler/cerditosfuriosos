#ifndef VISTAMANZANA_H_
#define VISTAMANZANA_H_

#include "VistaCuerpo.h"
#include "Manzana.h"

class VistaManzana: public VistaCuerpo {
public:
	/**
	 * Constructor.
	 * @param escenario puntero a la vista a la que le notificaremos cambios
	 * @param manzana referencia al objeto observado.
	 */
	VistaManzana(VistaEscenario* escenario, Manzana* manzana);
	virtual ~VistaManzana();
};

#endif
