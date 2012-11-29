#ifndef THREADCLIENTE_H_
#define THREADCLIENTE_H_

// Hierarchy Include.
#include "../../common/thread/Thread.h"

// Common Project Includes.
#include "../../common/communication/ThreadEnviar.h"
#include "../../common/communication/ThreadRecibir.h"

// Forward Class Declaration
class Server;
class ThreadPartida;

/**
 * @class ThreadCliente
 * Thread que maneja la comunicacion con el cliente.
 */
class ThreadCliente : public Thread {
public:
	ThreadCliente(Server& servidor, Socket* socket);

	virtual ~ThreadCliente();

	void setPartida(ThreadPartida* partida);

	/*
	 * @brief relaciona a un jugador dentro del escenario con
	 * un cliente conectado.
	 * @param id del jugador
	 */
	void asignarJugador(unsigned int id);

	/*
	 * @brief
	 * @return devuelve el id del jugador manejado por el cliente
	 */
	unsigned int getJugadorAsignado();

	/*
	 * @brief valida que haya eventos enviado por el cliente
	 */
	bool hayEventos();

	/*
	 * @brief desencola un evento recibido del cliente
	 * @return evento
	 */
	Evento desencolarEvento();

	/*
	 * @brief encola mensajes para ser enviados asincronicamente
	 * @param m mensaje
	 */
	void enviar(Mensaje* m);

	/*
	 * @brief recibe mensajes asincronicamente en una cola
	 * @return mensaje
	 */
	Mensaje* recibir();

	/*
	 * @brief finaliza ejecucion
	 */
	void finalizar();

protected:
	void* run();

private:
	// TODO provisorio
	void correrJuego();

	// Flag que indica si el cliente está conectado.
	bool conectado;

	// id del jugador manejado por el cliente dentro de la partida
	unsigned int idJugador;

	// Socket mediante el cual realiza comunciaciones con el cliente.
	Socket* socket;

	// Referencia a la partida conectada
	ThreadPartida* threadPartida;

	// Referencia del servidor
	Server& server;

	ColaProtegida<Evento> colaEventos;

	// threads para envio y recibo de mensajes
	ThreadEnviar* tEnviar;
	ThreadRecibir* tRecibir;
};

#endif /* THREADCLIENTE_H_ */
