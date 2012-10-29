#ifndef DISPARO_H_
#define DISPARO_H_

// Hierarchy Include.
#include "CuerpoAbstracto.h"

// Project Includes.
#include "Jugador.h"
#include "Superficie.h"
#include "Pajaro.h"
#include "Cerdito.h"

/* @class Disparo
 * Daña otros cuerpos de la escena como superficies y aplica puntos al jugador
 * que realizo el disparo.
 */
class Disparo: public CuerpoAbstracto {
public:
	// Constructor por default.
	Disparo();

	// Destructor.
	virtual ~Disparo();

	/* Choca el disparo con una superficie aplicandole un daño y asignando
	 * puntos al jugador en caso de que fue destruida.
	 * @param Superficie a chocar.
	 */
	virtual void chocarCon(Superficie* superficie) = 0;

	/* Choca el disparo con un pájaro aplicandole un daño y asignando
	 * puntos al jugador en caso de que fue matado.
	 * @param Pájaro a chocar.
	 */
	virtual void chocarCon(Pajaro* pajaro) = 0;

	/* Choca el disparo con un cerdito aplicandole un daño.
	 * @param Cerdito a chocar.
	 */
	virtual void chocarCon(Cerdito* cerdito) = 0;

protected:
	// Jugador que realiza el disparo.
	Jugador* jugador;

	// Daño que el disparo realiza a pájaros
	float danioPajaro;

	// Daño que el disparo realiza a superficies
	float danioSuperficie;
};

#endif /* DISPARO_H_ */
