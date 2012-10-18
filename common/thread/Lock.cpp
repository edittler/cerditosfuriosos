/* Implementación de la clase Lock que hace uso del patrón de diseño RAII.
 * Bloquea el mutex en su construcción y lo desbloquea en su destrucción.
 */

// Project Includes
#include "Lock.h"

Lock::Lock(Mutex& mutex):m(mutex) {
	this->m.lock();
}

Lock::~Lock() {
	this->m.unlock();
}
