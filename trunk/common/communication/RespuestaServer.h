#ifndef RESPUESTASERVER_H_
#define RESPUESTASERVER_H_

// Hierarchy Include.
#include "Mensaje.h"

/**
 * Enumerado que lista los valores que puede adquirir la respuesta del server.
 */
enum RespuestaServidor {
	RS_INDEFINIDA,			// Respuesta indefinida.
	RS_TABLA_RECORDS,		// Enviar la lista de records.
	RS_LISTA_MUNDOS,		// Enviar mundos para la creacion de una nueva partida.
	RS_LISTA_PARTIDAS,		// Enviar partidas ya creadas.
	RS_UNIRSE_PARTIDA_OK,	// Confirmacion para unirse a una partida especificada.
	RS_UNIRSE_PARTIDA_ERROR	// Aviso de error al intentar unirse a una partida.
};

/**
 * Mensaje que el servidor en respuesta a un mensaje que recibió del cliente.
 * Ofrece servicios, como mostrar la tabla de records, crear una partida,
 * unirse a una existente, abandonar partida o enviar los eventos del juego.
 */
class RespuestaServer: public Mensaje {
public:
	/**
	 * Constructor que setea el mensaje RespuestaServidor con el tipo especificado.
	 * Útil para usar en comandos sencillos como RS_UNIRSE_PARTIDA_ERROR.
	 * @param tipo de respuesta que se va a enviar
	 */
	RespuestaServer(RespuestaServidor tipo = RS_INDEFINIDA);

	/**
	 * Constructor que setea el mensaje RespuestaServidor con el tipo
	 * especificado y los datos establecidos.
	 * Útil para usar en comandos como RS_TABLA_RECORDS, RS_LISTA_MUNDOS,
	 * RS_LISTA_PARTIDAS.
	 * @param tipo de respuesta que se va a enviar.
	 * @param datos que se van a enviar.
	 */
	RespuestaServer(RespuestaServidor tipo, const std::string& datos);

	/**
	 * Constructor que setea el mensaje RespuestaServidor con el tipo
	 * RS_UNIRSE_PARTIDA_OK y el id del jugador especificado.
	 * @param idJugador a enviar.
	 */
	RespuestaServer(unsigned int idJugador);

	virtual ~RespuestaServer();

	/**
	 * @brief serializa la informacion de la clase a cadena de char.
	 * @return cadena de char serializados exprasados como un string.
	 */
	std::string serealizar() const;

	/**
	 * @brief deserializa la informacion de la clase a partir de una
	 * cadena de char.
	 * @param cadena de char a deserializar.
	 */
	void deserealizar(const std::string& mensaje);

	/**
	 * Setea el mensaje RespuestaServidor con el tipo especificado.
	 * Útil para usar en comandos sencillos como RS_UNIRSE_PARTIDA_ERROR.
	 * @param tipo de respuesta que se va a enviar
	 */
	void set(RespuestaServidor tipo);

	/**
	 * Setea el mensaje RespuestaServidor con el tipo especificado y los datos
	 * establecidos
	 * Útil para usar en comandos como RS_TABLA_RECORDS, RS_LISTA_MUNDOS,
	 * RS_LISTA_PARTIDAS.
	 * @param tipo de respuesta que se va a enviar.
	 * @param datos que se van a enviar.
	 */
	void set(RespuestaServidor tipo, const std::string& datos);

	/**
	 * Setea el mensaje RespuestaServidor con el tipo RS_UNIRSE_PARTIDA_OK y
	 * el id del jugador especificado.
	 * @param idJugador a enviar.
	 */
	void set(unsigned int idJugador);

	RespuestaServidor getTipoRespuesta() const;

	std::string getDatos() const;

private:
	void decodificarDatos(const std::string& mensaje);

	void decodificarIDJugador(const std::string& mensaje);

	// Tipo de respuesta que envia el server.
	RespuestaServidor tipo;

	/**
	 * String que contiene datos enviados.
	 * Será usado cuando se envian los comandos RS_TABLA_RECORDS,
	 * RS_LISTA_MUNDOS, RS_LISTA_PARTIDAS.
	 */
	std::string datos;

	unsigned int idJugador;
};

#endif /* RESPUESTASERVER_H_ */
