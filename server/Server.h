#ifndef SERVER_H_
#define SERVER_H_

#include <map>
#include <list>
#include <string>

#include "SocketServer.h"
#include "ThreadCliente.h"
#include "thread/Mutex.h"
#include "communication/ConstantesClientServer.h"

// Abreviaturas usadas para contenedores.
//typedef std::list<std::pair<std::string, unsigned int> > ListaRecords;
//typedef std::map<std::string, ListaRecords> TablaRecords;

//typedef std::map<unsigned int, ThreadPartida* >PartidasDisponibles;
typedef std::list<ThreadCliente*> ClientesEnEspera;

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
	 * @brief registra y comienza un nuevo Thread destinado a manejar
	 * comunicaciones directamente con el cliente.
	 * @param nuevo thread a registrar.
	 */
	void registrarCliente(ThreadCliente* cliente);

private:
	bool encendido;
	unsigned short int port;

	SocketServer* socket;
//	Mutex* mutexSocket;
//	TablaRecords* records;
//	PartidasDisponibles* partidasDisponibles;
	ClientesEnEspera* clientesEnEspera;

	friend class ThreadListener;
};

#endif /* SERVER_H_ */
