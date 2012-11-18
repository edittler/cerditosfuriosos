#ifndef SERVER_H_
#define SERVER_H_

// Hierarchy Include.
#include "../../common/thread/Thread.h"

// C++ Library Includes.
#include <map>
#include <string>

// Common Project Includes.
#include "../../common/thread/Mutex.h"
#include "../../common/communication/Socket.h"
#include "../../common/communication/ConstantesClientServer.h"

// Server Project Includes.
#include "DefinicionesServidor.h"
#include "ThreadCliente.h"
#include "ThreadPartida.h"
#include "Partida.h"

/**
 * Server
 * Administra partidas, acepta conexiones de clientes y los atiende.
 */
class Server: private Thread {
public:
	/**
	 * Constructor por defecto
	 */
	Server();

	/**
	 * Constructor con parámetros
	 * @param port Puerto desde el cual se desea realizar conexiones.
	 */
	Server(Puerto port);

	/**
	 * Destructor
	 */
	virtual ~Server();

	/**
	 * Enciende el servidor, habilitando el puerto para escuchar conexiones,
	 * aceptar conexiones entrantes y atender a los clientes.
	 */
	void prender();
	void apagar();

	/**
	 * Crea una partida nueva
	 * @param
	 * @param
	 */
	void crearPartida(Partida* partida, ThreadCliente* cliente);

private:
	/**
	 * @brief metodo asincronico donde se aceptan conexiones entrantes.
	 * Una vez aceptada la conexion se delega su administracion a un
	 * nuevo Thread.
	 */
	void* run();

	bool encendido;

	// Socket por el cual se realizan las comunicaciones en red.
	Socket* socket;

	/* Tabla de records */
//	TablaRecords* records;

	/* Partidas creadas */
	PartidasDisponibles partidasDisponibles;

	/* Clientes conectados */
	ClientesConectados clientesConectados;
};

#endif /* SERVER_H_ */
