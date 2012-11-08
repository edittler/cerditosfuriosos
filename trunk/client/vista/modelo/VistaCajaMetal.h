#ifndef VISTACAJAMETAL_H_
#define VISTACAJAMETAL_H_

#include "VistaCuerpo.h"
#include "CajaMetal.h"

class VistaCajaMetal: public VistaCuerpo {
public:
	/**
	 * Constructor.
	 * @param escenario puntero a la vista a la que le notificaremos cambios
	 * @param caja referencia al objeto observado.
	 */
	VistaCajaMetal(VistaEscenario* escenario, CajaMetal* caja);
	virtual ~VistaCajaMetal();
};

#endif /* VISTACAJAMETAL_H_ */
