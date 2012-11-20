#ifndef THREADRECIBIR_H_
#define THREADRECIBIR_H_

#include "../thread/Thread.h"

#include "ColaProtegida.h"
#include "MensajeCliente.h"
#include "Socket.h"

class ThreadRecibir: public Thread {
public:
	ThreadRecibir(Socket* socket);
	virtual ~ThreadRecibir();

	Mensaje* getMensaje();

	void* run();

private:

	// flag para indicar finalizacion de recibos.
	bool terminado;

	// cola de mensajes recibidos.
	ColaProtegida<Mensaje*> mensajes;

	Socket* socket;

};

#endif /* THREADRECIBIR_H_ */
