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
	 * Constructor con parametros.
	 * @param tipo Tipo de respuesta que se va a crear.
	 */
	RespuestaServer(RespuestaServidor tipo = RS_INDEFINIDA);

	/**
	 * Constructor con parametros
	 * @param tipo Tipo de respuesta que se va a crear.
	 * @param datos Los datos que se van a enviar en la respuesta, como la tabla
	 * de records, la lista de mundos, la lista de partidas ya creadas.
	 */
	RespuestaServer(RespuestaServidor tipo, const std::string& datos);

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

	RespuestaServidor getTipoRespuesta() const;

	std::string getDatos() const;

private:
	void decodificarDatos(const std::string& mensaje);

	// Tipo de respuesta que envia el server.
	RespuestaServidor tipo;

	// String que contiene los datos
	std::string datos;
};

#endif /* RESPUESTASERVER_H_ */
