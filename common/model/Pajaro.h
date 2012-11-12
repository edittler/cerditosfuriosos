#ifndef PAJARO_H_
#define PAJARO_H_

// Hierarchy Include.
#include "CuerpoAbstracto.h"

// Project Includes.
#include "Superficie.h"
#include "Cerdito.h"
#include "Fruta.h"
#include "Monticulo.h"

/* Clase base Párajo, una abstraccion generica de los pájaros que son lanzados
 * en el juego Cerditos Furiosos.
 * Contienen información como el daño que le realiza a las superficies y a los
 * cerditos.
 */
class Pajaro: public CuerpoAbstracto {
public:
	/* @brief Constructor con parametros.
	 * @param b2Body de Box2D asociado al pajaro.
	 * @param vida del pajaro.
	 * @param danio que realiza a los cerditos
	 * @param danio que realiza a las superficies
	 */
	explicit Pajaro(b2Body* body, float vida, int danioCerditos,
			int danioSuperficies);

	// Destructor
	virtual ~Pajaro();

	/*
	 * @brief Choca el Pájaro con una Superficie, aplicandole un daño.
	 * @param Superficie a la que se quiere chocar.
	 */
	void chocarCon(Superficie* superficie);

	/*
	 * @brief Choca Pajaro con Cerdito, aplicandole un daño
	 * @param Cerdito al que se quiere chocar.
	 */
	void chocarCon(Cerdito* cerdito);

	/*
	 * @brief Choca Pajaro con Fruta, elimandola del juego.
	 * @param Fruta a la que se quiere chocar.
	 */
	void chocarCon(Fruta* fruta);

	/*
	 * @brief Choca Pajaro con Monticulo, elimandola del juego.
	 * @param Monticulo a la que se quiere chocar.
	 */
	void chocarCon(Monticulo* monticulo);

protected:
	// Daño que le realiza a los Cerditos al chocarlos.
	float danioCerdito;

	// Daño que le realiza a las Superficies al chocarlas.
	float danioSuperficie;
};

#endif  /* PAJARO_H_ */
