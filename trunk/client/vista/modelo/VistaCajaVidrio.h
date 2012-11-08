#ifndef VISTACAJAVIDRIO_H_
#define VISTACAJAVIDRIO_H_

#include "VistaCuerpo.h"
#include "CajaVidrio.h"

class VistaCajaVidrio: public VistaCuerpo {
public:
	/**
	 * Constructor.
	 * @param escenario puntero a la vista a la que le notificaremos cambios
	 * @param caja referencia al objeto observado.
	 */
	VistaCajaVidrio(VistaEscenario* escenario, CajaVidrio* caja);
	virtual ~VistaCajaVidrio();
};

#endif /* VISTACAJAVIDRIO_H_ */
