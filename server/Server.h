#ifndef SERVER_H_
#define SERVER_H_

// C++ Library Includes.
#include <map>
#include <string>

// Project Includes.
#include "SocketServer.h"
#include "ThreadCliente.h"
#include "ThreadPartida.h"
#include "thread/Mutex.h"
#include "communication/ConstantesClientServer.h"

// Abreviaturas usadas para contenedores.
//typedef std::list<std::pair<std::string, unsigned int> > ListaRecords;
//typedef std::map<std::string, ListaRecords> TablaRecords;

typedef std::map<unsigned int, ThreadPartida* > PartidasDisponibles;

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

	unsigned short int port;
	SocketServer* socket;

	/* Tabla de records */
//	TablaRecords* records;

	/* Partidas creadas */
	PartidasDisponibles partidasDisponibles;

	/* Clientes conectados */
	ClientesConectados clientesConectados;

	friend class ThreadListener;
};

#endif /* SERVER_H_ */
