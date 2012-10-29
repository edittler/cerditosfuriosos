#ifndef CERDITO_H_
#define CERDITO_H_

// Hierarchy Include.
#include "CuerpoAbstracto.h"

// Project Includes.
#include "Catapulta.h"

/* Clase Cerdito, abstraccion del cerdito que aparece en el juego
 * Cerditos Furiosos.
 */
class Cerdito: public CuerpoAbstracto {
public:
	/* Constructor con b2Body especificado para darle atributos correspondientes
	 * @param b2Body asociado al World de la libreria Box2D.
	 */
	explicit Cerdito(b2Body* body, Catapulta* catapulta);

	// Destructor
	virtual ~Cerdito();

private:
	// Catapulta del cerdito
	Catapulta* catapulta;
};

#endif /* CERDITO_H_ */
