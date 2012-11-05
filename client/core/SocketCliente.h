#ifndef SOCKETCLIENTE_H_
#define SOCKETCLIENTE_H_

#include <netdb.h>

#include "Socket.h"

/*
 * @class SocketCliente
 * Clase que encapsula el comportamiento de un socket cliente.
 */
class SocketCliente: public Socket {
public:
	SocketCliente();
	SocketCliente(int fd);
	virtual ~SocketCliente();

	void conectar(const char* serverIp, unsigned short int port);
};

#endif /* SOCKETCLIENTE_H_ */
