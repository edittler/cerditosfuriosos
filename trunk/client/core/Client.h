#ifndef CLIENT_H_
#define CLIENT_H_

#include <Socket.h>

class Client {
public:
	Client();
	Client(const char* ip, unsigned short int port);
	virtual ~Client();

	/*
	 * @brief conecta al ip y puerto especificado.
	 */
	void conectar();

	/*
	 * @brief cierra conexion del socket en forma ordenada
	 * mediante metodo shutdown.
	 */
	void desconectar();

	/*
	 * @brief intercambia mensajes con el server hasta que se
	 * especifique cerrar la comunicacion.
	 */
	bool ejecutar();

private:

	void correrJuego();
	Socket* socket;

	std::string serverIp;
	unsigned short int port;
};

#endif /* CLIENT_H_ */
