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

	/* @brief Registra un observador. Solo puede registrar un único observador,
	 * en caso de querer agregar más, se lanzará excepciones.
	 * @param Observador a registrar.
	 */
	void registrarObservador(ObservadorEscenario* observador);

	/* @brief Elimina el observador. En caso de que no haya un observador
	 * registrado, no realiza nada.
	 */
	void eliminarObservador();

protected:
	// Observador registrado.
	ObservadorEscenario* observador;
};

#endif /* ESCENARIOOBSERVABLE_H_ */
