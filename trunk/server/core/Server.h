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
	 * @brief Enciende el servidor, habilitando el puerto para escuchar conexiones,
	 * aceptar conexiones entrantes y atender a los clientes.
	 * @return true si prendio correctamente, false caso contrario.
	 */
	bool prender();
	void apagar();

	/**
	 * Crea una partida nueva
	 * @param
	 * @param
	 */
	void crearPartida(Partida* partida, ThreadCliente* cliente);

	/*
	 * @brief agrega el @cliente a la partida @idPartida
	 * @param id de la partida
	 * @param cliente a unir
	 */
	bool unirseAPartida(unsigned int idPartida, ThreadCliente* cliente);

	/*
	 * @brief obtiene una lista de los nombres de mundos disponibles
	 * @return	lista de nombres de mundos
	 */
	std::list<std::string> getMundosDisponibles() const;

	/*
	 * @brief devuelve el path del xml correspondiente al @id
	 * @param id del mundo
	 * @return path del XML asociado al @id
	 */
	std::string getPathXMLMundo(std::string id) const;

	/*
	 * @brief devuelve un string de la forma: idPartida + ":" + nombrePartida
	 * @return lista.
	 */
	std::list<std::string> getPartidasDisponibles();

	/*
	 * @brief devuelve la tabla de records asociada al @nivel
	 * @param nivel del cual se quieren ver los records
	 */
	ListaRecords getTablaRecords(std::string nivel);

private:

	/**
	 * Elimina referencias a clientes desconectados.
	 */
	void limpiarThreadClientes();

	/**
	 * Elimina referencias a partidas ya finalizadas
	 */
	void limpiarThreadPartidas();

	/*
	 * @brief carga nombres y paths de mapas disponibles
	 */
	void cargarInformacionMundos();

	/*
	 * @brief en caso de no existir el archivo que contiene los mundos
	 */
	void crearArchivoMundos();

	/**
	 * @brief metodo asincronico donde se aceptan conexiones entrantes.
	 * Una vez aceptada la conexion se delega su administracion a un
	 * nuevo Thread.
	 */
	void* run();

	bool encendido;

	// Socket por el cual se realizan las comunicaciones en red.
	Socket* socket;

	/* Mundos disponibles */
	MundosDisponibles mundosDiponibles;

	/* Tabla de records */
	TablaRecords records;

	/* Partidas creadas */
	Mutex mPartidas;
	PartidasDisponibles partidasDisponibles;

	/* Clientes conectados */
	Mutex mClientes;
	ClientesConectados clientesConectados;
};

#endif /* SERVER_H_ */
