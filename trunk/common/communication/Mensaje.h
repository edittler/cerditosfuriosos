#ifndef MENSAJE_H_
#define MENSAJE_H_

// C++ Library Includes.
#include <string>

/**
 * Clase abstracta base de los mensajes enviados entre cliente - server.
 */
class Mensaje {
public:
	Mensaje() {}
	virtual ~Mensaje() {}

	/**
	 * @brief serializa la informacion de la clase a cadena de char.
	 * @return cadena de char serializados exprasados como un string.
	 */
	virtual std::string serealizar() const = 0;

	/**
	 * @brief deserializa la informacion de la clase a partir de una
	 * cadena de char.
	 * @param cadena de char a deserializar.
	 */
	virtual void deserealizar(const std::string& mensaje) = 0;
};

#endif /* MENSAJE_H_ */
