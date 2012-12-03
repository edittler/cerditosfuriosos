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
	/* @brief Constructor con b2Body especificado para darle atributos
	 * correspondientes.
	 * @param b2Body asociado al World de la libreria Box2D.
	 * @param catapulta correspondiente al cerdito.
	 * @param nodo XML que contiene informacion del cerdito.
	 */
	explicit Cerdito(b2Body* body, Catapulta* catapulta);

	// Destructor
	virtual ~Cerdito();

	/* Serializa el Cerdito y lo retorna en un nodo XML */
	XMLNode* serialize();

	/* A partir de un nodo XML se establece el Cerdito */
	void hydrate(const XMLNode* nodo);

	/* @brief Retorna la catapulta asociada al cerdito.
	 */
	Catapulta* getCatapulta();

private:
	// Catapulta del cerdito
	Catapulta* catapulta;
};

#endif /* CERDITO_H_ */
