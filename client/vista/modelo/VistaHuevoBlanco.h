#ifndef VISTAHUEVOBLANCO_H_
#define VISTAHUEVOBLANCO_H_

#include "VistaCuerpo.h"
#include "HuevoBlanco.h"

class VistaHuevoBlanco: public VistaCuerpo {
public:
	/**
	 * Constructor.
	 * @param escenario puntero a la vista a la que le notificaremos cambios
	 * @param referencia al objeto observado.
	 */
	VistaHuevoBlanco(VistaEscenario* escenario, HuevoBlanco* huevo);

	/**
	 * Destructor.
	 */
	virtual ~VistaHuevoBlanco();
};

#endif /* VISTAHUEVOBLANCO_H_ */
