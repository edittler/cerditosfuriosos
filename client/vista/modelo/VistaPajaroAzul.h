#ifndef VISTAPAJAROAZUL_H_
#define VISTAPAJAROAZUL_H_

#include "VistaCuerpo.h"
#include "PajaroAzul.h"

class VistaPajaroAzul: public VistaCuerpo {
public:

	/**
	 * Constructor.
	 * @param escenario puntero a la vista a la que le notificaremos cambios
	 * @param caja referencia al objeto observado.
	 */
	VistaPajaroAzul(VistaEscenario* escenario, PajaroAzul* pajaro);
	virtual ~VistaPajaroAzul();
};

#endif /* VISTAPAJAROAZUL_H_ */
