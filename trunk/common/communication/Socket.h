#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

#include "Mensaje.h"

#define MAX_LENGTH_MESSAGE 1024

class Socket {
public:
	Socket();
	Socket(int fd);
	virtual ~Socket();

	/*
	 * @brief Envia datos a traves del socket.
	 * @param Mensaje a enviar.
	 */
	void enviar(Mensaje* mensaje);

	/*
	 * @brief Recibe datos a traves del socket.
	 * @return Mensaje recibido.
	 */
	void recibir(Mensaje* mensaje);

	/*
	 * @brief Cierra el envio y recepcion de datos en forma ordenada.
	 * Llama internamente al metodo shutdown();
	 */
	void desconectar();

protected:
	int fd;  // file descriptor
	bool error;
};

#endif /* SOCKET_H_ */
