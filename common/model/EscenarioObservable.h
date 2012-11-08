#ifndef ESCENARIOOBSERVABLE_H_
#define ESCENARIOOBSERVABLE_H_

// Project Include.
#include "ObservadorEscenario.h"

/* @class EscenarioObservable
 * Interfaz que define que un Escenario puede ser observado, según el patrón
 * observador. Permite tener un solo observador.
 */
class EscenarioObservable {
public:
	// @brief Constructor por defecto
	EscenarioObservable();

	// @brief Destructor
	virtual ~EscenarioObservable();

	/* @brief Registra un observador.
	 * @param Observador a registrar.
	 */
	virtual void registrarObservador(ObservadorEscenario* observador) = 0;

	/* @brief Elimina el observador especificado.
	 * En caso de que no exista el observador especificado lanza una excepcion.
	 */
	virtual void eliminarObservador(ObservadorEscenario* observador) = 0;
};

#endif /* ESCENARIOOBSERVABLE_H_ */
