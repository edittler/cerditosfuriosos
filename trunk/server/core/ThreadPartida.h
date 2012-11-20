#ifndef THREADPARTIDA_H_
#define THREADPARTIDA_H_

// Hierarchy Include.
#include "../../common/thread/Thread.h"

// C++ Library Includes.
#include <list>

// Common Project Includes.
#include "../../common/communication/ColaProtegida.h"

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

	/*
	 * @brief comienza la partida
	 */
	void comenzarPartida();

	/*
	 * @brief une cliente a partida.
	 * @param cliente a agregar.
	 */
	void unirseAPartida(ThreadCliente* cliente);

	/*
	 * @brief pausa partida.
	 */
	void pausarPartida();

	/*
	 * @brief finaliza partida.
	 */
	void finalizarPartida();


	void* run();

	unsigned int getId();

private:
	/**
	 * Agrega un jugador a la partida.
	 * @param cliente que se desea agregar.
	 * @return Retorna true si se pudo agregar el cliente o false en caso
	 * contrario.
	 */
	bool agregarJugador(ThreadCliente* cliente);

	// identificador de la partida.
	unsigned int id;

	// TODO agregar mutex
	Partida* partida;

	/* Cola de eventos que se va usar para que los clientes carguen eventos.
	 * Su implementación ya contempla un mutex para protegerlo.
	 */
	ColaProtegida<Evento*> eventos;

	ClientesConectados jugadores;

};

#endif /* THREADPARTIDA_H_ */
