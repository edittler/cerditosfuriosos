#ifndef THREADPARTIDA_H_
#define THREADPARTIDA_H_

#include <list>
#include <Thread.h>

#include "Partida.h"
#include "ThreadCliente.h"

typedef std::list<ThreadCliente*> ClientesConectados;

class ThreadPartida: public Thread {
public:
	ThreadPartida(Partida* partida);
	virtual ~ThreadPartida();

	/*
	 * @brief comienza la partida
	 */
	void comenzarPartida();

	/*
	 * @brief finaliza partida
	 */
	void finalizarPartida();


	void* run();

private:

	// agregar mutex
	Partida* partida;

	ClientesConectados jugadores;
};

#endif /* THREADPARTIDA_H_ */
