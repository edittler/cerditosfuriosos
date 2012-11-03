#ifndef CUERPOOBSERVABLE_H_
#define CUERPOOBSERVABLE_H_

// Project Includes.
#include "ObservadorCuerpo.h"

/* @class CuerpoObservable
 * Interfaz que define que un cuerpo puede ser observado, según el patrón
 * observador.
 */
class CuerpoObservable {
public:

	CuerpoObservable();

	virtual ~CuerpoObservable();

	/* @brief Registra un observador. Solo puede registrar un único observador,
	 * en caso de querer agregar más, se lanzará excepciones.
	 * @param Observador a registrar.
	 */
	void registrarObservador(ObservadorCuerpo* observador);

	/* @brief Elimina el observador. En caso de que no haya un observador
	 * registrado, no realiza nada.
	 */
	void eliminarObservador();

protected:
	// Observador registrado.
	ObservadorCuerpo* observador;
};

#endif /* CUERPOOBSERVABLE_H_ */
