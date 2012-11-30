#ifndef THREADENVIAR_H_
#define THREADENVIAR_H_

#include "../thread/Thread.h"

#include "ColaProtegida.h"
#include "RespuestaServer.h"
#include "Socket.h"

class ThreadEnviar: public Thread {
public:
	ThreadEnviar(Socket& socket);
	virtual ~ThreadEnviar();

	void agregarMensaje(Mensaje* mensaje);

	void finalizar();

	void* run();

private:

	// flag para indicar finalizacion de envios.
	bool terminado;

	// cola de mensajes a enviar.
	ColaProtegida<Mensaje*> mensajes;

	Socket& socket;
};

#endif /* THREADENVIAR_H_ */
