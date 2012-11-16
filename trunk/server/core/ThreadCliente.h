#ifndef THREADCLIENTE_H_
#define THREADCLIENTE_H_

// Hierarchy Include.
#include "../../common/thread/Thread.h"

// Project Includes.
#include "../../common/communication/Socket.h"

/**
 * @class ThreadCliente
 * Thread que maneja la comunicacion con el cliente.
 */
class ThreadCliente : public Thread {
public:
	ThreadCliente();
	ThreadCliente(Socket* socket);
	virtual ~ThreadCliente();

	virtual void* run();

private:
	// Flag que indica si el cliente está conectado.
	bool conectado;
	Socket* socket;
};

#endif /* THREADCLIENTE_H_ */
