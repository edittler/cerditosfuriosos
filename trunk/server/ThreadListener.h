#ifndef THREADLISTENER_H_
#define THREADLISTENER_H_

#include "Server.h"

#include "thread/Thread.h"

/*
 * @class ThreadListener
 * Thread usado para aceptar conexiones entrantes.
 */
class ThreadListener : public Thread {
public:
	ThreadListener();
	ThreadListener(Server* server);
	virtual ~ThreadListener();

	/*
	 * @brief metodo asincronico donde se aceptan conexiones entrantes.
	 * Una vez aceptada la conexion se delega su administracion a un
	 * nuevo Thread.
	 */
	virtual void* run();

private:
	Server* server;
};

#endif /* THREADLISTENER_H_ */
