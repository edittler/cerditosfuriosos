#ifndef BANANA_H_
#define BANANA_H_

// Hierarchy Include.
#include "Fruta.h"

class Banana: public Fruta {
public:
	/* @brief Constructor con parametros.
	 * @param b2Body de Box2D asociado a la fruta.
	 */
	explicit Banana(b2Body* body);

	// Destructor
	virtual ~Banana();

	/* @brief Serializa la Banana y lo retorna en un nodo XML */
	XMLNode* serialize();

	/* @brief Como el CuerpoAbstracto requiere del b2Body para realizar
	 * operaciones básicas, no se puede hidratar desde un nodo, salvo algunos
	 * atributos.
	 */
	void hydrate(const XMLNode* nodo);
};

#endif /* BANANA_H_ */
