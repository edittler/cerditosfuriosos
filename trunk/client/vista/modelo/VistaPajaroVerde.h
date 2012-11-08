#ifndef VISTAPAJAROVERDE_H_
#define VISTAPAJAROVERDE_H_

#include "VistaCuerpo.h"
#include "PajaroVerde.h"

class VistaPajaroVerde: public VistaCuerpo {
public:
	/**
	 * Constructor.
	 * @param escenario puntero a la vista a la que le notificaremos cambios.
	 * @param referencia al objeto observado.
	 */
	VistaPajaroVerde(VistaEscenario* escenario, PajaroVerde* pajaro);
	virtual ~VistaPajaroVerde();
};

#endif /* VISTAPAJAROVERDE_H_ */
