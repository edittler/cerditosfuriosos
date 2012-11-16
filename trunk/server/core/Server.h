#ifndef SERVER_H_
#define SERVER_H_

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

/*
 * @class Server
 * TODO
 */
class Server {
public:
	Server();
	Server(unsigned short int port);
	virtual ~Server();

	void prender();
	void apagar();

	/*
	 * @brief crea una partida nueva
	 * @param
	 * @param
	 */
	void crearPartida();

	/*
	 * @brief registra y comienza un nuevo Thread destinado a manejar
	 * comunicaciones directamente con el cliente.
	 * @param nuevo thread a registrar.
	 */
	void registrarCliente(ThreadCliente* cliente);

private:
	bool encendido;

	Socket* socket;

	/* Tabla de records */
//	TablaRecords* records;

	/* Partidas creadas */
	PartidasDisponibles partidasDisponibles;

	/* Clientes conectados */
	ClientesConectados clientesConectados;

	friend class ThreadListener;
};

#endif /* SERVER_H_ */
