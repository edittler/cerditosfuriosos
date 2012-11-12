#ifndef MANZANA_H_
#define MANZANA_H_

// Hierarchy Include.
#include "Fruta.h"

class Manzana: public Fruta {
public:
	/* @brief Constructor con parametros.
	 * @param b2Body de Box2D asociado a la fruta.
	 */
	explicit Manzana(b2Body* body);

	// Destructor
	virtual ~Manzana();

	/* @brief Serializa la Manzana y lo retorna en un nodo XML */
	XMLNode* serialize();

	/* @brief Como el CuerpoAbstracto requiere del b2Body para realizar
	 * operaciones básicas, no se puede hidratar desde un nodo, salvo algunos
	 * atributos.
	 */
	void hydrate(const XMLNode* nodo);
};

#endif /* MANZANA_H_ */
