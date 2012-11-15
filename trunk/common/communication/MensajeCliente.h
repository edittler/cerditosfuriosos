#ifndef MENSAJECLIENTE_H_
#define MENSAJECLIENTE_H_

// Hierarchy Include.
#include "Mensaje.h"

/**
 * Enumerado que lista los valores que puede adquirir el comando del cliente.
 */
typedef enum ComandoClienteValues {
	ComandoNoDefinido,	// Comando indefinido.
	VerRecords,			// Ver la lista de records.
	CrearPartida,		// Creacion de una nueva partida.
	VerPartidas,		// Ver partidas ya creadas.
	UnirsePartida,		// Unirse a una partida especificada.
	Evento,				// Modo envio de evento.
	Desconectar 		// Abandonar la partida.
} ComandoCliente;

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
	explicit MensajeCliente(ComandoCliente comando = ComandoNoDefinido);

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
