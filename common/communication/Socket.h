#ifndef SOCKET_H_
#define SOCKET_H_

#include <netinet/in.h>

#include "Mensaje.h"

typedef unsigned short int Puerto;

class Socket {
public:
	/* @brief Constructor con parametros.
	 * @param Numero del puerto desde el cual se desea realizar conexiones.
	 */
	explicit Socket(Puerto puerto);

	// Destructor
	virtual ~Socket();

	/* @brief Enlaza el socket en la direccion de la propia PC
	 */
	bool enlazar();

	/* @brief Habilita el socket para escuchar conexiones entrantes.
	 */
	bool escucharConexiones(int maxConexiones);

	/* @brief Acepta una nueva conexión entrante y retorna un puntero al
	 * socket remoto.
	 * Si retorna NULL, fallo la operación.
	 */
	Socket* aceptarConexion();

	/* @brief Establecer una conexion con el servidor.
	 * @param string que contiene la direccion IP a la cual se conectara el socket.
	 */
	bool conectar(const std::string serverAddr);

	/* @brief Establecer una conexion con el servidor.
	 * @param string que contiene la direccion a la cual se conectara el socket.
	 */
	bool conectarPorNombre(const std::string serverAddr);

	/* @brief Cierra el envio y recepcion de datos en forma ordenada.
	 */
	void desconectar();

	/*
	 * @brief Envia datos a traves del socket.
	 * @param Mensaje a enviar.
	 */
	bool enviar(const Mensaje& mensaje);

	/*
	 * @brief Recibe datos a traves del socket.
	 * @return Mensaje recibido.
	 */
	void recibir(Mensaje& mensaje);

	bool estaConectado() const;

protected:
	// Inicializa los atributos del socket.
	void inicializar();

	// File Descriptor del socket
	int fd;

	// Puerto desde el cual se va a conectar
	Puerto puerto;

	// Dirección del socket
	struct sockaddr_in direccion;

	// Flag que indica si el socket se encuentra enlazado con otro socket.
	bool enlazado;

	// Flag que indica si el socket se encuentra conectado con otro socket.
	bool conectado;

private:
	/* Constructor con int como parametro.
	 */
	Socket(int fd);

	/* Constructor copia de la clase Socket.
	 */
	Socket(const Socket& sock);

	/* Operador de asignaciòn de la clase Socket.
	 */
	Socket& operator=(const Socket& sock);
};

#endif /* SOCKET_H_ */
