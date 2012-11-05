#ifndef THREADCLIENTE_H_
#define THREADCLIENTE_H_

#include "thread/Thread.h"

#include "communication/Socket.h"

/*
 * @class ThreadCliente
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
