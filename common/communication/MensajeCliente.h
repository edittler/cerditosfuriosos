#ifndef MENSAJECLIENTE_H_
#define MENSAJECLIENTE_H_

// Hierarchy Include.
#include "Mensaje.h"

/**
 * Enumerado que lista los valores que puede adquirir el comando del cliente.
 */
enum ComandoCliente {
	MC_INDEFINIDO,			// Comando indefinido.
	MC_VER_RECORDS,			// Ver la lista de records.
	MC_CREAR_PARTIDA,		// Creacion de una nueva partida.
	MC_VER_PARTIDAS,		// Ver partidas ya creadas.
	MC_UNIRSE_PARTIDA,		// Unirse a una partida especificada.
	MC_EVENTO,				// Modo envio de evento.
	MC_DESCONECTAR 			// Abandonar la partida.
};

/**
 * Mensaje que el cliente envía al servidor.
 * Solicita servicios, como mostrar la tabla de records, crear una partida,
 * unirse a una existente, abandonar partida o enviar los eventos del juego.
 */
class MensajeCliente: public Mensaje {
public:
	/**
	 * Constructor con parametros.
	 * @param comando Comando con el que se quiere inicializar el mensaje.
	 */
	explicit MensajeCliente(ComandoCliente comando = MC_INDEFINIDO);

	/**
	 * Constructor con parametros.
	 * @param evento Evento con el que se quiere inicializar el mensaje.
	 */
	MensajeCliente(std::string partidaID);

	/**
	 * Constructor con parametros.
	 * @param evento Evento con el que se quiere inicializar el mensaje.
	 */
	//MensajeCliente(Evento evento);

	/**
	 * Destructor.
	 */
	virtual ~MensajeCliente();

	/**
	 * Serializa el mensaje en un string.
	 * @return String con el mensaje serializado.
	 */
	std::string serealizar() const;

	/**
	 *
	 */
	void deserealizar(const std::string& mensaje);

	/**
	 * Permite obtener el comando que tiene cargado el Mensaje.
	 * @return Retorna el comando.
	 */
	ComandoCliente getComando() const;

private:
	void decodificarPartida(const std::string& mensaje);

	// Comando que tiene cargado el mensaje del cliente.
	ComandoCliente comando;

	// Identificador de la partida a la que se quiere unir.
	std::string partida;
};

#endif /* MENSAJECLIENTE_H_ */
