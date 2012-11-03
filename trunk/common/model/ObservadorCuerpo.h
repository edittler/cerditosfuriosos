#ifndef OBSERVADORCUERPO_H_
#define OBSERVADORCUERPO_H_

// Project Includes.
#include "Punto2D.h"

/* @class ObservadorCuerpo
 * Interfaz de un caso particular del patrón observador para los objetos del
 * escenario.
 */
class ObservadorCuerpo {
public:
	ObservadorCuerpo();

	virtual ~ObservadorCuerpo();

	/* @brief Actualiza la posición del observador en base al cambio en el modelo.
	 * @param La nueva posicion del cuerpo del modelo.
	 */
	virtual void actualizarPosicion(Punto2D posicion) = 0;

	/* @brief Avisa al observador que el cuerpo se murió.
	 */
	virtual void seMurio() = 0;
};

#endif /* OBSERVADORCUERPO_H_ */
