#ifndef PAJAROAZUL_H_
#define PAJAROAZUL_H_

// Hierarchy Include.
#include "Pajaro.h"

class PajaroAzul: public Pajaro {
public:
	/* @brief Constructor con parametros.
	 * @param b2Body de Box2D asociado al pajaro.
	 */
	explicit PajaroAzul(b2Body* body);

	// Destructor
	virtual ~PajaroAzul();

	/* @brief Serializa el Pajaro Azul y lo retorna en un nodo XML */
	XMLNode* serialize();

	/* @brief Como el CuerpoAbstracto requiere del b2Body para realizar
	 * operaciones básicas, no se puede hidratar desde un nodo, salvo algunos
	 * atributos.
	 */
	void hydrate(const XMLNode* nodo);
};

#endif /* PAJAROAZUL_H_ */
