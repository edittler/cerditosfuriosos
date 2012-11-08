#ifndef VISTAHUEVORELOJ_H_
#define VISTAHUEVORELOJ_H_

#include "VistaCuerpo.h"
#include "HuevoReloj.h"

class VistaHuevoReloj: public VistaCuerpo {
public:
	/**
	 * Constructor.
	 * @param escenario puntero a la vista a la que le notificaremos cambios
	 * @param referencia al objeto observado.
	 */
	VistaHuevoReloj(VistaEscenario* escenario, HuevoReloj* huevo);
	virtual ~VistaHuevoReloj();
};

#endif /* VISTAHUEVORELOJ_H_ */
