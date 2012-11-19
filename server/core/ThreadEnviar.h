#ifndef THREADENVIAR_H_
#define THREADENVIAR_H_

#include <Thread.h>

#include "../../common/communication/ColaProtegida.h"
#include "../../common/communication/RespuestaServer.h"
#include "../../common/communication/Socket.h"

class ThreadEnviar: public Thread {
public:
	ThreadEnviar(Socket* socket);
	virtual ~ThreadEnviar();

	void agregarMensaje(RespuestaServer* mensaje);

	void* run();

private:

	// flag para indicar finalizacion de envios.
	bool terminado;

	// cola de mensajes a enviar.
	ColaProtegida<RespuestaServer*> mensajes;

	Socket* socket;
};

#endif /* THREADENVIAR_H_ */
