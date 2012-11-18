#ifndef CLIENT_H_
#define CLIENT_H_

// Common Project Includes.
#include <Socket.h>

/**
 * Cliente
 * Clase que implementa la logica de comunicaciones con el servidor en el modo
 * multijugador del juego.
 */
class Client {
public:
	/**
	 * Constructor por default
	 * Se conecta al servidor mediante la dirección IP de loopback (localhost)
	 * y el puerto por default establecido por el server desarrollado.
	 */
	Client();

	/**
	 * Constructor con parámetros
	 * @param ip Dirección IP del server a conectarse.
	 * @param port Puerto que desea usarse para conectarse.
	 */
	Client(std::string ip, Puerto port);

	/**
	 * Destructor
	 */
	virtual ~Client();

	/**
	 * Se conecta al servidor.
	 * @return Retorna true si se pudo conectar con el server o false en caso
	 * contrario.
	 */
	bool conectar();

	/**
	 * Cierra conexion con el servidor en forma ordenada mediante el método
	 * shutdown.
	 */
	void desconectar();

	/**
	 * Muestra las pantallas correspondientes al modo multijugador e intercambia
	 * mensajes con el servidor para obtener las informaciones solicitadas.
	 */
	void ejecutar();

private:

	void crearPartida();

	void unirsePartida();

	void verRecords();

	void correrJuego();  // FIXME Provisorio, no va aca.

	// Socket mediante el cual se realizan las comunicaciones con el server.
	Socket* socket;

	// Puerto mendiante el cual se realizan las comunicaciones.
	Puerto port;

	// Dirección IP del server.
	std::string serverIp;

	// Booleanto que especifica si el cliente está corriendo o no.
	bool corriendo;
};

#endif /* CLIENT_H_ */
