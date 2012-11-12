#ifndef THREADCLIENTE_H_
#define THREADCLIENTE_H_

// Hierarchy Include.
#include "../common/thread/Thread.h"

// Project Includes.
#include "../common/communication/Socket.h"

/* @class ThreadCliente
 * Thread que maneja la comunicacion con el cliente.
 */
class ThreadCliente : public Thread {
public:
	ThreadCliente();
	ThreadCliente(int fd);
	virtual ~ThreadCliente();

	virtual void* run();

private:
	Socket* socket;
};

#endif /* THREADCLIENTE_H_ */
