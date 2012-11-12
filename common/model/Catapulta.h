#ifndef CATAPULTA_H_
#define CATAPULTA_H_

// Hierarchy Include.
#include "CuerpoAbstracto.h"

/* Clase Catapulta, abstraccion de la catapulta que aparece en el juego
 * Cerditos Furiosos.
 */
class Catapulta: public CuerpoAbstracto {
public:
	/* @brief Constructor con b2Body especificado para darle atributos
	 * correspondientes.
	 * @param b2Body asociado al World de la libreria Box2D.
	 * @param nodo XML que contiene informacion del cerdito.
	 */
	explicit Catapulta(b2Body* body);

	// Destructor.
	virtual ~Catapulta();

	/* @brief Serializa la catapulta y retorna un nodo XML
	 */
	XMLNode* serialize();

	/* @brief A partir de un nodo XML se establece atributos de la catapulta.
	 * @param Nodo XML del cual obtener los atributos de la catapulta.
	 */
	void hydrate(const XMLNode* nodo);
};

#endif /* CATAPULTA_H_ */
