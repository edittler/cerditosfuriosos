#ifndef SOCKETSERVER_H_
#define SOCKETSERVER_H_

#include "communication/Socket.h"

/*
 * @class SocketServer
 * Clase que encapsula el comportamiento de un socket server.
 */
class SocketServer : public Socket {
public:
	SocketServer();
	SocketServer(int fd);
	virtual ~SocketServer();

	/*
	 * @brief enlaza el file descriptor con una direccion y puerto locales.
	 * @param numero de puerto donde esta corriendo el server.
	 */
	void enlazar(unsigned int port);

	/*
	 * @brief
	 * @param cantidad maxima de clientes en espera para ser aceptados.
	 */
	void escuchar(unsigned int maxWait);

	/*
	 * @brief Acepta conexiones entrantes, metodo bloqueante.
	 * @return Devuelve el file descriptor del socket aceptado.
	 */
	int aceptar();
};

#endif /* SOCKETSERVER_H_ */
