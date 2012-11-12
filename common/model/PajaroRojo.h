#ifndef PAJAROROJO_H_
#define PAJAROROJO_H_

// Hierarchy Include.
#include "Pajaro.h"

class PajaroRojo: public Pajaro {
public:
	/* @brief Constructor con parametros.
	 * @param b2Body de Box2D asociado al pajaro.
	 */
	explicit PajaroRojo(b2Body* body);

	// Destructor
	virtual ~PajaroRojo();

	/* @brief Serializa el Pajaro Rojo y lo retorna en un nodo XML */
	XMLNode* serialize();

	/* @brief Como el CuerpoAbstracto requiere del b2Body para realizar
	 * operaciones básicas, no se puede hidratar desde un nodo, salvo algunos
	 * atributos.
	 */
	void hydrate(const XMLNode* nodo);
};

#endif  /* PAJAROROJO_H_ */
