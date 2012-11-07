#ifndef CUERPOOBSERVABLE_H_
#define CUERPOOBSERVABLE_H_

// Project Includes.
#include "ObservadorCuerpo.h"

/* @class CuerpoObservable
 * Interfaz que define que un cuerpo puede ser observado, según el patrón
 * observador. Permite tener un solo observador.
 */
class CuerpoObservable {
public:

	CuerpoObservable();

	virtual ~CuerpoObservable();

	/* @brief Registra un observador.
	 * @param Observador a registrar.
	 */
	virtual void registrarObservador(ObservadorCuerpo* observador) = 0;

	/* @brief Elimina el observador. En caso de que no exista el observador
	 * dado, no realiza nada.
	 */
	virtual void eliminarObservador(ObservadorCuerpo* observador) = 0;
};

#endif /* CUERPOOBSERVABLE_H_ */
