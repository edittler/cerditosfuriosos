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

	/* @brief Choca el disparo con una superficie aplicandole un daño y asignando
	 * puntos al jugador en caso de que fue destruida.
	 * @param Superficie a chocar.
	 */
	virtual void chocarCon(Superficie* superficie);

	/* @brief Choca el disparo con un pájaro aplicandole un daño y asignando
	 * puntos al jugador en caso de que fue matado.
	 * @param Pájaro a chocar.
	 */
	virtual void chocarCon(Pajaro* pajaro);

	/* Choca el disparo con un cerdito aplicandole un daño.
	 * @param Cerdito a chocar.
	 */
	virtual void chocarCon(Cerdito* cerdito);

	/* @brief Choca el disparo con el monticulo.
	 * @param monticulo a chocar.
	 */
	virtual void chocarCon(Monticulo* monticulo);

	/* @brief Choca el disparo con una fruta obteniendo los puntos.
	 * @param Fruta a chocar.
	 */
	virtual void chocarCon(Fruta* fruta);

protected:
	// Jugador que realiza el disparo.
	Jugador* jugador;

	// Daño que el disparo realiza a pájaros
	float danioPajaro;

	// Daño que el disparo realiza a superficies
	float danioSuperficie;
};

#endif /* DISPARO_H_ */
