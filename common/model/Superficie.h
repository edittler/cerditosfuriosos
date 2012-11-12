#ifndef SUPERFICIE_H_
#define SUPERFICIE_H_

// Hierarchy Include.
#include "CuerpoAbstracto.h"

class Superficie: public CuerpoAbstracto {
public:
	/* @brief Constructor con parametros
	 * @param body asociado al cuerpo.
	 * @param vida del cuerpo.
	 * @param puntos que otorga la superficie al ser destruida.
	 */
	explicit Superficie(b2Body* body, float vida, int puntosDestruccion);

	// Destructor
	virtual ~Superficie();

	/* Retorna los puntos de destruccion que otorga
	 */
	int getPuntosDestruccion() const;

protected:
	int puntosDestruccion;
};

#endif /* SUPERFICIE_H_ */
