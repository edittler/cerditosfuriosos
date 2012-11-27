#ifndef THREADRECIBIRCLIENTE_H_
#define THREADRECIBIRCLIENTE_H_

#include <Thread.h>

#include "ColaProtegida.h"
#include "MensajeServer.h"
#include "Socket.h"

class ThreadRecibirCliente: public Thread {
public:
	ThreadRecibirCliente(Socket& socket);
	virtual ~ThreadRecibirCliente();

	Mensaje* getMensaje();

	void* run();

private:

	// flag para indicar finalizacion de recibos.
	bool terminado;

	// cola de mensajes recibidos.
	ColaProtegida<Mensaje*> mensajes;

	Socket& socket;
};

#endif /* THREADRECIBIRCLIENTE_H_ */
