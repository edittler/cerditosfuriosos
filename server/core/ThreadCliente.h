#ifndef THREADCLIENTE_H_
#define THREADCLIENTE_H_

// Hierarchy Include.
#include "../../common/thread/Thread.h"

// Project Includes.
#include "../../common/communication/Socket.h"

// Forward Class Declaration
class Server;

/**
 * @class ThreadCliente
 * Thread que maneja la comunicacion con el cliente.
 */
class ThreadCliente : public Thread {
public:
	ThreadCliente(Server& servidor, Socket* socket);

	virtual ~ThreadCliente();

	virtual void* run();

private:
	// TODO provisorio
	void correrJuego();

	// Flag que indica si el cliente está conectado.
	bool conectado;

	// Socket mediante el cual realiza comunciaciones con el cliente.
	Socket* socket;

	// Referencia del servidor
	Server& server;
};

#endif /* THREADCLIENTE_H_ */
