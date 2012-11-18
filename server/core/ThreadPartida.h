#ifndef THREADPARTIDA_H_
#define THREADPARTIDA_H_

// Hierarchy Include.
#include "../../common/thread/Thread.h"

// C++ Library Includes.
#include <list>

// Common Project Includes.
#include "../../common/communication/ColaEventos.h"

// Server Project Includes.
#include "DefinicionesServidor.h"
#include "Partida.h"
#include "ThreadCliente.h"

class ThreadPartida: public Thread {
public:
	/**
	 * Constructor que recibe informacion de la partida y el cliente que la
	 * está creando.
	 */
	ThreadPartida(Partida* partida, ThreadCliente* cliente);
	virtual ~ThreadPartida();

	/**
	 * Agrega un jugador a la partida.
	 * @param cliente que se desea agregar.
	 * @return Retorna true si se pudo agregar el cliente o false en caso
	 * contrario.
	 */
	bool agregarJugador(ThreadCliente* cliente);

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

	/* Cola de eventos que se va usar para que los clientes carguen eventos.
	 * Su implementación ya contempla un mutex para protegerlo.
	 */
	ColaEventos eventos;

	ClientesConectados jugadores;
};

#endif /* THREADPARTIDA_H_ */
