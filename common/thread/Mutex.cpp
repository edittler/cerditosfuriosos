/* Implementación de la clase Mutex que encapsula el mutex de la librería
 * POSIX Thread
 */

// Project Includes
#include "Mutex.h"

Mutex::Mutex() {
	// Inicializa el mutex POSIX Thread que encapsula.
	pthread_mutex_init(&(this->m), NULL);
}

Mutex::~Mutex() {
	// Destruye el mutex POSIX Thread que encapsula.
	pthread_mutex_destroy(&(this->m));
}

void Mutex::lock() {
	// Bloquea el mutex POSIX Thread que encapsula.
	pthread_mutex_lock(&(this->m));
}

void Mutex::unlock() {
	// Desbloquea el mutex POSIX Thread que encapsula.
	pthread_mutex_unlock(&(this->m));
}
