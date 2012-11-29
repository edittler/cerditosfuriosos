#ifndef THREADPARTIDA_H_
#define THREADPARTIDA_H_

// Hierarchy Include.
#include "../../common/thread/Thread.h"

// C++ Library Includes.
#include <list>

// Common Project Includes.
#include "../../common/communication/ColaProtegida.h"
#include "Mutex.h"

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
	 * @brief finaliza ejecucion de la partida.
	 */
	void finalizar();

	/*
	 * @brief comienza la partida
	 */
	void comenzarPartida();

	/*
	 * @brief une cliente a partida.
	 * @param cliente a agregar.
	 * @return true si pudo agregar, false caso contrario.
	 */
	bool unirseAPartida(ThreadCliente* cliente);

	/*
	 * @brief elimina cliente de la partida.
	 * @param cliente a eliminar
	 */
	void abandonarPartida(ThreadCliente* cliente);
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
	std::string getNombrePartida() const;

private:
	/*
	 * @brief Agrega un jugador a la partida.
	 * @param cliente que se desea agregar.
	 * @return Retorna true si se pudo agregar el cliente o false en caso
	 * contrario.
	 */
	bool agregarJugador(ThreadCliente* cliente);

	/*
	 * @brief elimina a un jugador de la partida, liberando el id
	 * del jugador en el escenario y eliminandolo de la lista de
	 * clientes conectados a la partida.
	 * @param cliente a eliminar
	 * @return true si puedo eliminar, false caso contrario.
	 */
	bool eliminarJugador(ThreadCliente* cliente);

	/*
	 * @brief recibe mensajes enviados por los clientes y los
	 * procesa. Si fuese necesario reenvia o informa dicho
	 * mensaje a demas clientes conectados.
	 */
	void procesarMensajesClientes();

	/*
	 * @brief procesa los eventos generados posteriores a correr
	 * un tick en el esceneario y los notifica a los clientes.
	 */
	void procesarMensajesParaClientes();

	// Flag para indicar si el ThreadPartida sigue conectado.
	bool conectado;

	Mutex mPartida;
	Partida* partida;

	Mutex mJugadores;
	ClientesConectados jugadores;
};

#endif /* THREADPARTIDA_H_ */
