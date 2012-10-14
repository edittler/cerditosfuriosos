/* Interfaz de la clase Mutex que encapsula el mutex de la librería POSIX Thread
 */

#ifndef MUTEX_H_
#define MUTEX_H_

// POSIX Thread Library Includes
#include <pthread.h>

class Mutex {
private:
	/**************
	 * ATTRIBUTES *
	 **************/
	pthread_mutex_t m;  // POSIX Thread mutex

public:
	/*******************************
	 * CONSTRUCTORS AND DESTRUCTOR *
	 *******************************/
	/* Crea el mutex */
	Mutex();

	/* Destruye el mutex */
	virtual ~Mutex();

	/***********************
	 * METHODS MUTEX CLASS *
	 ***********************/
	/* Solicita el bloqueo del mutex.
	 * Si ya se encuentra bloqueado, la ejecución del hilo queda suspendido
	 * hasta que se desbloquee.
	 */
	void lock();

	/* Desbloquea el mutex.
	 * El mutex queda disponible para ser bloqueado por otro hilo que esté
	 * suspendido.
	 */
	void unlock();

private:
	/*******************************
	 * PRIVATE METHODS MUTEX CLASS *
	 *******************************/
	/* Constructor copia privado de la clase Mutex */
	Mutex(const Mutex& m);

	/* Operador de asignacion privado de la clase Mutex. */
	Mutex& operator=(const Mutex& otherInstance);
};

#endif /* MUTEX_H_ */
