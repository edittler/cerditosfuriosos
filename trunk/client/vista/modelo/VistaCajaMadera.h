#ifndef VISTACAJAMADERA_H_
#define VISTACAJAMADERA_H_

#include "VistaCuerpo.h"
#include "CajaMadera.h"

class VistaCajaMadera: public VistaCuerpo {
public:
	/**
	 * Constructor.
	 * @param escenario puntero a la vista a la que le notificaremos cambios
	 * @param caja referencia al objeto observado.
	 */
	VistaCajaMadera(VistaEscenario* escenario, CajaMadera* caja);

	/**
	 * Destructor.
	 */
	virtual ~VistaCajaMadera();
};

#endif /* VISTACAJAMADERA_H_ */
