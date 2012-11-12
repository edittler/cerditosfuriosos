#ifndef MONTICULO_H_
#define MONTICULO_H_

// Hierarchy Include.
#include "CuerpoAbstracto.h"

class Monticulo: public CuerpoAbstracto {
public:
	/* @brief Constructor que recibe el b2Body de Box2D.
	 */
	explicit Monticulo(b2Body* body);

	// Destructor
	virtual ~Monticulo();

	/* @brief Serializa el Monticulo y lo retorna en un nodo XML */
	XMLNode* serialize();

	/* @brief Como el CuerpoAbstracto requiere del b2Body para realizar
	 * operaciones básicas, no se puede hidratar desde un nodo, salvo algunos
	 * atributos.
	 */
	void hydrate(const XMLNode* nodo);
};

#endif
