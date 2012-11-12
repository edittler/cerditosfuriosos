#ifndef CEREZA_H_
#define CEREZA_H_

// Hierarchy Include.
#include "Fruta.h"

class Cereza: public Fruta {
public:
	/* @brief Constructor con parametros.
	 * @param b2Body de Box2D asociado a la fruta.
	 */
	explicit Cereza(b2Body* body);

	// Destructor
	virtual ~Cereza();

	/* @brief Serializa la Cereza y lo retorna en un nodo XML */
	XMLNode* serialize();

	/* @brief Como el CuerpoAbstracto requiere del b2Body para realizar
	 * operaciones básicas, no se puede hidratar desde un nodo, salvo algunos
	 * atributos.
	 */
	void hydrate(const XMLNode* nodo);
};

#endif /* CEREZA_H_ */
