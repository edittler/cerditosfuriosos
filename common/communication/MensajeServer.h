#ifndef MENSAJESERVER_H_
#define MENSAJESERVER_H_

// Hierarchy Include.
#include "Mensaje.h"

/**
 * Enumerado de los valores que puede adquirir el comando del cliente.
 */
enum ComandoServer {
	MS_NO_DEFINIDO,			// Comando indefinido.
	MS_CARGAR_NIVEL,		// Cargar nivel, junto con los datos del nivel
	MS_EVENTO,				// Comando server que indica que se envia un evento.
	MS_FINALIZAR_NIVEL,		// Finalizar nivel.
	MS_FINALIZAR_PARTIDA	// Finalizar partida.
};

class MensajeServer: public Mensaje {
public:
	MensajeServer(ComandoServer comando = MS_NO_DEFINIDO);
	virtual ~MensajeServer();

	virtual std::string serealizar() const;
	virtual void deserealizar(const std::string& mensaje);

	ComandoServer getComando() const;

private:
	// Comando que contiene el mensaje del servidor.
	ComandoServer comando;

	// String con los datos que contiene el mensaje del servidor.
	std::string datos;

	// Evento que contiene el mensaje del servidor.
//	Evento* evento;
};

#endif /* MENSAJESERVER_H_ */
