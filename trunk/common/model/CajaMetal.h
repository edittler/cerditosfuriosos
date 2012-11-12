#ifndef CAJAMETAL_H_
#define CAJAMETAL_H_

// Hierarchy Include.
#include "Superficie.h"

class CajaMetal: public Superficie {
public:
	/* @brief Constructor que recibe el body asociado y define los atributos
	 * y propiedades de la Caja de Metal.
	 */
	explicit CajaMetal(b2Body* body);

	// Destructor
	virtual ~CajaMetal();

	/* @brief Serializa la Caja de Metal y lo retorna en un nodo XML */
	XMLNode* serialize();

	/* @brief Como el CuerpoAbstracto requiere del b2Body para realizar
	 * operaciones básicas, no se puede hidratar desde un nodo, salvo algunos
	 * atributos.
	 */
	void hydrate(const XMLNode* nodo);
};

#endif /* CAJAMETAL_H_ */
