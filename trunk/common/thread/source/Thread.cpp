/*
 * Thread.cpp
 *
 *  Created on: 14/10/2012
 *      Author: ezequiel
 */

#include "../include/Thread.h"

Thread::Thread() { }

Thread::~Thread() { }

int Thread::start() {
	// Creo el POSIX thread
	return pthread_create(&thread, 0, start_routine, this);
}

void* Thread::join() {
	void* result;  // Puntero void donde se va a almacenar el resultado
	// Ejecuto el POSIX thread join
	pthread_join(thread, &result);
	return result;
}

void* Thread::start_routine(void* arg) {
	Thread* r = (Thread*) arg;
	void* resultado = r->run();
	return resultado;
}
