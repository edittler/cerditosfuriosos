#ifndef CAJAMADERA_H_
#define CAJAMADERA_H_

// Hierarchy Include.
#include "Superficie.h"

class CajaMadera: public Superficie {
public:
	/* @brief Constructor que recibe el body asociado y define los atributos
	 * y propiedades de la Caja de Madera.
	 */
	explicit CajaMadera(b2Body* body);

	// Destructor
	virtual ~CajaMadera();

	/* @brief Serializa la Caja de Madera y lo retorna en un nodo XML */
	XMLNode* serialize();

	/* @brief Como el CuerpoAbstracto requiere del b2Body para realizar
	 * operaciones básicas, no se puede hidratar desde un nodo, salvo algunos
	 * atributos.
	 */
	void hydrate(const XMLNode* nodo);
};

#endif /* CAJAMADERA_H_ */
