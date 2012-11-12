#ifndef CAJAVIDRIO_H_
#define CAJAVIDRIO_H_

// Hierarchy Include.
#include "Superficie.h"

class CajaVidrio: public Superficie {
public:
	/* @brief Constructor que recibe el body asociado y define los atributos
	 * y propiedades de la Caja de Vidrio.
	 */
	explicit CajaVidrio(b2Body* body);

	// Destructor
	virtual ~CajaVidrio();

	/* @brief Serializa la Caja de Vidrio y lo retorna en un nodo XML */
	XMLNode* serialize();

	/* @brief Como el CuerpoAbstracto requiere del b2Body para realizar
	 * operaciones básicas, no se puede hidratar desde un nodo, salvo algunos
	 * atributos.
	 */
	void hydrate(const XMLNode* nodo);
};

#endif /* CAJAVIDRIO_H_ */
