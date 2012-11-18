#ifndef MENSAJESERVER_H_
#define MENSAJESERVER_H_

// Hierarchy Include.
#include "Mensaje.h"

// Project Includes.
#include "Evento.h"

/**
 * Enumerado de los valores que puede adquirir el comando del cliente.
 */
enum ComandoServer {
	MS_INDEFINIDO,			// Comando indefinido.
	MS_CARGAR_NIVEL,		// Cargar nivel, junto con los datos del nivel
	MS_EVENTO,				// Comando server que indica que se envia un evento.
	MS_FINALIZAR_NIVEL,		// Finalizar nivel.
	MS_FINALIZAR_PARTIDA	// Finalizar partida.
};

class MensajeServer: public Mensaje {
public:
	/**
	 * Constructor con parametros.
	 * @param comando Define el tipo de mensaje que envia el server.
	 */
	MensajeServer(ComandoServer comando = MS_INDEFINIDO);

	/**
	 * Constructor que setea el mensaje con el comando evento.
	 * @param evento El evento que se desea enviar.
	 */
	MensajeServer(Evento evento);

	virtual ~MensajeServer();

	std::string serealizar() const;
	void deserealizar(const std::string& mensaje);

	void setEvento(Evento evento);

	ComandoServer getComando() const;

	Evento getEvento() const;

private:
	void deserealizarEvento(const std::string& mensaje);

	// Comando que contiene el mensaje del servidor.
	ComandoServer comando;

	// String con los datos que contiene el mensaje del servidor.
	std::string datos;

	// Evento que contiene el mensaje del servidor.
	Evento evento;
};

#endif /* MENSAJESERVER_H_ */
