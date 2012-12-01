#ifndef ARCHIVOCONFIGURACION_H_
#define ARCHIVOCONFIGURACION_H_

// C++ Library Includes.
#include <string>
#include <map>

/**
 * @class ArchivoConfiguracion
 * Es un tipo de archivo que contiene atributos levantados de un archivo
 * de texto. El archivo a levantar se encuentra encriptado.
 * Nota: esta clase no es thread-safe.
 */
class ArchivoConfiguracion {
public:
	/**
	 * Constructor por default que permite crear un nuevo archivo
	 */
	ArchivoConfiguracion();

	/**
	 * Constructor que recibe la ruta del archivo a editar/crear.
	 * @param ruta cadena de char que contiene la ruta del archivo.
	 */
	explicit ArchivoConfiguracion(const std::string ruta);

	/**
	 * Destructor
	 */
	virtual ~ArchivoConfiguracion();

	/**
	 * Retorna el valor del atributo especificado
	 * @param nombre string con el nombre del atributo del cual se desea el valor.
	 * @return string con el valor del atributo que se desea. Si la cadena está
	 * vacia, significa que no existe el atributo con el nombre especificado.
	 */
	std::string getAtributo(const std::string nombre);

	/**
	 * Setea el atributo con el valor especificado
	 * @param nombre string con el nombre del atributo que se desea setear.
	 * @param valor string con el valor que se desea setear en el atributo.
	 */
	void setAtributo(const std::string nombre, const std::string valor);

	/**
	 * Carga un archivo de configuración de la ruta especificada.
	 * @param ruta string que contiene la ruta del archivo de configuracion.
	 */
	bool cargar(const std::string ruta);

	/**
	 * Guarda el archivo de configuración en la ruta especificada anteriormente.
	 * Si no se especificó ninguna ruta, no se guarda nada.
	 */
	bool guardar() const;

	/**
	 * Guarda el archivo de configuración el la ruta especificada por parametro.
	 * @param ruta donde se desea guardar el archivo.
	 */
	bool guardar(const std::string ruta);

private:
	bool formatoCorrecto(const std::string& linea) const;

	// String que almacena la ruta del archivo de configuracion
	std::string rutaArchivo;

	// Mapa de atributo-valor
	std::map<std::string, std::string> atributos;
};

#endif /* ARCHIVOCONFIGURACION_H_ */
