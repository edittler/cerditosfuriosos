#ifndef THREADRECIBIR_H_
#define THREADRECIBIR_H_

#include <Thread.h>

#include "../../common/communication/ColaProtegida.h"
#include "../../common/communication/MensajeCliente.h"
#include "../../common/communication/Socket.h"

class ThreadRecibir: public Thread {
public:
	ThreadRecibir(Socket* socket);
	virtual ~ThreadRecibir();

	MensajeCliente* getMensaje();

	void* run();

private:

	// flag para indicar finalizacion de recibos.
	bool terminado;

	// cola de mensajes recibidos.
	ColaProtegida<MensajeCliente*> mensajes;

	Socket* socket;

};

#endif /* THREADRECIBIR_H_ */
