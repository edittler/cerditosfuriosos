#ifndef PAJAROVERDE_H_
#define PAJAROVERDE_H_

// Hierarchy Include.
#include "Pajaro.h"

class PajaroVerde: public Pajaro {
public:
	/* @brief Constructor con parametros.
	 * @param b2Body de Box2D asociado al pajaro.
	 */
	explicit PajaroVerde(b2Body* body);

	// Destructor
	virtual ~PajaroVerde();

	/* @brief Serializa el Pajaro Verde y lo retorna en un nodo XML */
	XMLNode* serialize();

	/* @brief Como el CuerpoAbstracto requiere del b2Body para realizar
	 * operaciones básicas, no se puede hidratar desde un nodo, salvo algunos
	 * atributos.
	 */
	void hydrate(const XMLNode* nodo);
};

#endif  /* PAJAROVERDE_H_ */
