#ifndef VISTAHUEVOCODORNIZ_H_
#define VISTAHUEVOCODORNIZ_H_

#include "VistaCuerpo.h"
#include "HuevoCodorniz.h"

class VistaHuevoCodorniz: public VistaCuerpo {
public:
	/**
	 * Constructor.
	 * @param escenario puntero a la vista a la que le notificaremos cambios
	 * @param referencia al objeto observado.
	 */
	VistaHuevoCodorniz(VistaEscenario* escenario, HuevoCodorniz* huevo);
	virtual ~VistaHuevoCodorniz();
};

#endif /* VISTAHUEVOCODORNIZ_H_ */
