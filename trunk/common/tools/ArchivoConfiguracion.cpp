// Header Include.
#include "ArchivoConfiguracion.h"

// C++ Library Includes.
#include <fstream>

// Projetc Includes.
#include "Cifrador.h"

#define SEPARADOR '='

ArchivoConfiguracion::ArchivoConfiguracion() {
	this->rutaArchivo.clear();
	this->atributos.clear();
}

ArchivoConfiguracion::ArchivoConfiguracion(const std::string ruta) {
	this->rutaArchivo = ruta;
	this->atributos.clear();
	this->cargar(ruta);
}

ArchivoConfiguracion::~ArchivoConfiguracion() { }

std::string ArchivoConfiguracion::getAtributo(const std::string nombre) {
	std::string valor;
	if (atributos.find(nombre) != atributos.end()) {
		valor = atributos[nombre];
	}
	return valor;
}

void ArchivoConfiguracion::setAtributo(const std::string nombre,
		const std::string valor) {
	atributos[nombre] = valor;
}

bool ArchivoConfiguracion::cargar(const std::string ruta) {
	this->rutaArchivo = ruta;
	Cifrador c;
	std::fstream archivo(ruta.c_str(), std::ios_base::in);
	// Si el archivo no se pudo abrir, retorno false
	if (!archivo)
		return false;

	std::string aux;
	while(!archivo.eof()) {
		std::getline(archivo, aux);
		c.descifrar(aux);
		if (this->formatoCorrecto(aux)) {
			unsigned int posSeparador = aux.find_first_of(SEPARADOR);
			std::string nombre = aux.substr(0, posSeparador);
			std::string atributo = aux.substr(posSeparador + 1);
			if (nombre.size() && atributo.size())
				atributos[nombre] = atributo;
		}
	}
	archivo.close();
	return true;
}

bool ArchivoConfiguracion::guardar() const {
	if (this->rutaArchivo.empty())
		return false;
	std::fstream archivo(rutaArchivo.c_str(), std::fstream::out);
	if (!archivo)
		return false;
	std::map<std::string, std::string>::const_iterator it;
	Cifrador c;
	for (it = atributos.begin(); it != atributos.end(); ++it) {
		std::string aux = it->first + "=" + it->second;
		c.cifrar(aux);
		archivo << aux << std::endl;
	}
	archivo.close();
	return true;
}

bool ArchivoConfiguracion::guardar(const std::string ruta) {
	this->rutaArchivo = ruta;
	return this->guardar();
}

bool ArchivoConfiguracion::formatoCorrecto(const std::string& linea) const {
	return ((linea.find(SEPARADOR) != std::string::npos) &&
	(linea.find_first_of(SEPARADOR) == linea.find_last_of(SEPARADOR)));
}
