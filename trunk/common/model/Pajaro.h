#ifndef PAJARO_H_
#define PAJARO_H_

// Hierarchy Include.
#include "CuerpoAbstracto.h"

// Project Includes.
#include "Superficie.h"

/* Clase base Párajo, una abstraccion generica de los pájaros que son lanzados
 * en el juego Cerditos Furiosos.
 * Contienen información como el daño que le realiza a las superficies y a los
 * cerditos.
 */
class Pajaro: public CuerpoAbstracto {
public:
	Pajaro();
	virtual ~Pajaro();

	/* Choca el Pájaro con una Superficie, aplicandole un daño.
	 * @param Superficie a la que se quiere chocar.
	 */
	void chocarCon(Superficie* superficie);

protected:
	// Daño que le realiza a los Cerditos al chocarlos.
	float danioCerdito;

	// Daño que le realiza a las Superficies al chocarlas.
	float danioSuperficie;
};

#endif /* PAJARO_H_ */
