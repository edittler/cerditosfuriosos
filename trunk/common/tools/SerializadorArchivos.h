#ifndef SERIALIZADORARCHIVOS_H_
#define SERIALIZADORARCHIVOS_H_

#include <string>

#define DELIMITADOR "cambiame"
#define DELIMITADOR_TAM 8

class SerializadorArchivos {
public:
	SerializadorArchivos();
	virtual ~SerializadorArchivos();

	/**
	 * serializa un archivo a un string. Realiza la sistitucion
	 * necesaria de caracteres reservados para la deserializacino de mensajes.
	 * @param path del archivo
	 * @param string donde se serializa el archivo.
	 */
	void serializar(const std::string& path, std::string& archivo);

	/**
	 * deserializa un string y lo guarda en un archivo con el nombre
	 * indicado. Realiza la sistitucion necesaria de caracteres reservados
	 * para la deserializacino de mensajes.
	 * @param path donde guardar el archivo
	 * @param nombre del archivo a guardar
	 * @param mensaje a deserializar
	 */
	void deserializar(const std::string& path, std::string& archivo);
};

#endif /* SERIALIZADORARCHIVOS_H_ */
