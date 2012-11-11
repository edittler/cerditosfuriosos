#ifndef VISTACEREZA_H_
#define VISTACEREZA_H_

#include "VistaCuerpo.h"
#include "Cereza.h"

class VistaCereza: public VistaCuerpo {
public:
	/**
	 * Constructor.
	 * @param escenario puntero a la vista a la que le notificaremos cambios
	 * @param cereza referencia al objeto observado.
	 */
	VistaCereza(VistaEscenario* escenario, Cereza* cereza);
	virtual ~VistaCereza();
};

#endif
