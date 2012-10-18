/* Interfaz de la clase abstracta Thread que permite ejecutar una funcion
 * en un hilo independiente.
 */

#ifndef THREAD_H_
#define THREAD_H_

// POSIX Threads Library Includes
#include <pthread.h>

class Thread {
protected:
	/**************
	 * ATTRIBUTES *
	 **************/
	pthread_t thread;  // POSIX Thread

public:
	/*******************************
	 * CONSTRUCTORS AND DESTRUCTOR *
	 *******************************/
	Thread();
	virtual ~Thread();

	/*******************************
	 * PUBLIC METHODS THREAD CLASS *
	 *******************************/
	/* Crea y ejecuta el thread.
	 * Los valores de retorno son:
	 * 		· 0 si ha sido creado y ejecutado existosamente.
	 * 		· otro valor si ha ocurrido un error.
	 */
	int start();

	/* Bloquea la ejecucion hasta que el thread termine correctamente */
	void* join();

protected:
	/**********************************
	 * PROTECTED METHODS THREAD CLASS *
	 **********************************/
	/* Método virtual puro que debe ser implementado con la funcionalidad que
	 * se desee que ejecute el hilo en cuestión */
	virtual void * run() = 0;

private:
	/********************************
	 * PRIVATE METHODS THREAD CLASS *
	 ********************************/
	/* Constructor copia privado */
	Thread(const Thread&);

	/* Operador asignación privado */
	Thread& operator=(const Thread&);

	/* Método estático que va a ejecutar el thread de POSIX */
	static void* start_routine(void* arg);
};

#endif  /* THREAD_H_ */
