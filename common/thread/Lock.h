/* Interfaz de la clase Lock que hace uso del patrón de diseño RAII.
 * Bloquea el mutex en su construcción y lo desbloquea en su destrucción.
 */

#ifndef LOCK_H_
#define LOCK_H_

// Project Includes
#include "Mutex.h"

class Lock {
private:
	Mutex &m;  // Referencia del mutex a bloquear y desbloquear

public:
	/* Bloquea el mutex */
	explicit Lock(Mutex &mutex);

	/* Desbloquea el mutex */
	virtual ~Lock();

private:
	/* Constructor copia privado */
	Lock(const Lock&);

	/* Operador de asignacion privado */
	Lock& operator=(const Lock&);
};

#endif  /* LOCK_H_ */
