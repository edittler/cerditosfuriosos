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
	MS_PAUSAR_PARTIDA,		// Establece la partida en pausa.
	MS_FINALIZAR_PARTIDA	// Finalizar partida.
};

class MensajeServer: public Mensaje {
public:
	/**
	 * Constructor que setea el comando del mensaje.
	 * Útil para comandos simples como MS_PAUSAR_PARTIDA, MS_FINALIZAR_PARTIDA.
	 * @param comando Define el tipo de mensaje que envia el server.
	 */
	MensajeServer(ComandoServer comando = MS_INDEFINIDO);

	/**
	 * Constructor que setea el comando del mensaje en CARGAR_NIVEL y agrega
	 * el string que contiene el XML del nivel.
	 * @param xmlNivel en un string.
	 */
	MensajeServer(const std::string& xmlNivel);

	/**
	 * Constructor que setea el mensaje con el comando evento.
	 * @param evento El evento que se desea enviar.
	 */
	MensajeServer(Evento evento);

	virtual ~MensajeServer();

	std::string serealizar() const;

	void deserealizar(const std::string& mensaje);

	/**
	 * Setea el comando del mensaje.
	 * Útil para comandos simples como MS_PAUSAR_PARTIDA, MS_FINALIZAR_PARTIDA.
	 * @param comando Define el tipo de mensaje que envia el server.
	 */
	void set(ComandoServer comando);

	/**
	 * Setea el mensaje como CARGAR_NIVEL y asigna el string que contiene el
	 * xml con los datos del nivel.
	 * @param xmlNivel string con los datos del xml.
	 */
	void set(const std::string& xmlNivel);

	/**
	 * Setea el mensaje como EVENTO y asigna el evento especificado.
	 * @param evento a enviar.
	 */
	void set(Evento evento);

	ComandoServer getComando() const;

	std::string getXMLNivel() const;

	Evento getEvento() const;

private:
	void deserealizarXMLNivel(const std::string& mensaje);

	void deserealizarEvento(const std::string& mensaje);

	// Comando que contiene el mensaje del servidor.
	ComandoServer comando;

	// String con los datos que contiene el mensaje del servidor.
	std::string xml;

	// Evento que contiene el mensaje del servidor.
	Evento evento;
};

#endif /* MENSAJESERVER_H_ */
