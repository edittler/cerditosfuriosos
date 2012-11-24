#ifndef MENSAJECLIENTE_H_
#define MENSAJECLIENTE_H_

// Hierarchy Include.
#include "Mensaje.h"

// Project Includes.
#include "Evento.h"

/**
 * Enumerado que lista los valores que puede adquirir el comando del cliente.
 */
enum ComandoCliente {
	MC_INDEFINIDO,			// Comando indefinido.
	MC_VER_RECORDS,			// Ver la lista de records.
	MC_VER_MUNDOS,			// Ver lista de mundos para crear una partida.
	MC_CREAR_PARTIDA,		// Creacion de una nueva partida.
	MC_VER_PARTIDAS,		// Ver partidas ya creadas.
	MC_UNIRSE_PARTIDA,		// Unirse a una partida especificada.
	MC_EVENTO,				// Modo envio de evento.
	MC_ABANDONAR_PARTIDA,	// Abandonar la partida.
	MC_DESCONECTAR			// Desconectar del server
};

/**
 * Mensaje que el cliente envía al servidor.
 * Solicita servicios, como mostrar la tabla de records, crear una partida,
 * unirse a una existente, abandonar partida o enviar los eventos del juego.
 */
class MensajeCliente: public Mensaje {
public:
	/**
	 * Constructor que setea el mensaje con un comando especificado.
	 * Útil para usar con los comandos simples como MC_VER_RECORDS, MC_VER_MUNDOS,
	 * MC_VER_PARTIDAS, MC_ABANDONAR_PARTIDA, MC_DESCONECTAR.
	 * @param comando a enviar.
	 */
	explicit MensajeCliente(ComandoCliente comando = MC_INDEFINIDO);

	/**
	 * Constructor que setea el mensaje con un identificador del mundo y
	 * un nombre de la partida que desea crear.
	 * Se asigna automáticamente el comando MC_CREAR_PARTIDA.
	 * @param idMundo seleccionado para crear la partida.
	 * @param nombrePartida elegido para la nueva partida.
	 */
	MensajeCliente(std::string idMundo, std::string nombrePartida);

	/**
	 * Constructor que setea el mensaje con un identificador de la partida
	 * a la que desea unirse.
	 * Se asigna automáticamente el comando MC_UNIRSE_PARTIDA.
	 * @param idPartida a la que desea unirse.
	 */
	MensajeCliente(std::string idPartida);

	/**
	 * Constructor que setea el mensaje con un evento especificado.
	 * Se asigna automáticamente el comando MC_EVENTO.
	 */
	MensajeCliente(Evento evento);

	/**
	 * Destructor.
	 */
	virtual ~MensajeCliente();

	/**
	 * Serializa el evento en un string.
	 * @return String con el evento serializado.
	 */
	std::string serealizar() const;

	/**
	 *Deserealiza el evento a partir de un string especificado.
	 *@param mensaje string con el evento serealizado.
	 */
	void deserealizar(const std::string& mensaje);

	/**
	 * Setea el mensaje con un comando especificado.
	 * Útil para usar con los comandos simples como MC_VER_RECORDS, MC_VER_MUNDOS,
	 * MC_VER_PARTIDAS, MC_ABANDONAR_PARTIDA, MC_DESCONECTAR.
	 * @param comando a enviar.
	 */
	void set(ComandoCliente comando);

	/**
	 * Setea el mensaje con un identificador del mundo y un nombre de la partida.
	 * Se asigna automáticamente el comando MC_CREAR_PARTIDA.
	 * @param idMundo seleccionado para crear la partida.
	 * @param nombrePartida elegido para la nueva partida.
	 */
	void set(std::string idMundo, std::string nombrePartida);

	/**
	 * Setea el mensaje con un identificador de la partida a la que desea unirse.
	 * Se asigna automáticamente el comando MC_UNIRSE_PARTIDA.
	 * @param idPartida seleccionado para unirse.
	 */
	void set(std::string idPartida);

	/**
	 * Setea el mensaje con un evento especificado.
	 * Se asigna automáticamente el comando MC_EVENTO.
	 * @param evento a enviar.
	 */
	void set(Evento evento);

	/**
	 * Permite obtener el comando que tiene cargado el Mensaje.
	 * @return Retorna el comando.
	 */
	ComandoCliente getComando() const;

	std::string getID() const;

	std::string getNombrePartida() const;

	Evento getEvento() const;

private:
	/**
	 * Decodifida el ID que puede contener el mensaje.
	 * Además, si el mensaje contiene el comando MC_CREAR_PARTIDA, decodifica
	 * el nombre de la partida elegido.
	 * @param mensaje el mismo string que recibió el metodo deserealizar.
	 */
	void decodificarParametros(const std::string& mensaje);

	/**
	 * Decodifica el evento que puede contener el mensaje.
	 * @param mensaje el mismo string que recibió el metodo deserealizar.
	 */
	void deserealizarEvento(const std::string& mensaje);

	// Comando que tiene cargado el mensaje del cliente.
	ComandoCliente comando;

	/* Identificador del mundo seleccionado para crear una partida o de la
	 * partida a la que se quiere unir.
	 */
	std::string id;

	// Nombre de la partida que se va a crear
	std::string nombre;

	// Evento que se envia en el mensaje
	Evento evento;
};

#endif /* MENSAJECLIENTE_H_ */
