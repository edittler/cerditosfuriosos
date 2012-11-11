#ifndef VISTAHUEVOPOCHE_H_
#define VISTAHUEVOPOCHE_H_

#include "VistaCuerpo.h"
#include "HuevoPoche.h"

class VistaHuevoPoche: public VistaCuerpo {
public:
	/**
	 * Constructor.
	 * @param escenario puntero a la vista a la que le notificaremos cambios
	 * @param referencia al objeto observado.
	 */
	VistaHuevoPoche(VistaEscenario* escenario, HuevoPoche* huevo);

	/**
	 * Destructor.
	 */
	virtual ~VistaHuevoPoche();
};

#endif
