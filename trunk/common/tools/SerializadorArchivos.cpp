#include "SerializadorArchivos.h"
#include <fstream>
#include "../log/Log.h"
#include "../tools/CFTools.h"

SerializadorArchivos::SerializadorArchivos() { }

SerializadorArchivos::~SerializadorArchivos() { }

void SerializadorArchivos::serializar(const std::string& path,
		std::string& archivo) {
	archivo.clear();
	std::ifstream file(path.c_str(), std::ifstream::in);

	if (file == NULL) {
		LOG_INFO("Archivo inexistente.")
		return;
	}

	// cargo archivo en string
	char c;
	while (!file.eof()) {
		file.get(c);
		if (c == '\n') {
			archivo.append(DELIMITADOR);
		} else {
			archivo.push_back(c);
		}
	}

	file.close();
}

using namespace std;

void SerializadorArchivos::deserializar(const std::string& path, std::string& archivo) {
	// creo archivo.
	std::ofstream file(path.c_str());

	if (file == NULL) {
		LOG_INFO("Error al crear archivo.")
		return;
	}

	// realizo intercambio
	size_t pos = 0;
	pos = archivo.find(DELIMITADOR, pos);
	while (pos != std::string::npos) {
		archivo.replace(pos, DELIMITADOR_TAM, "\n");
		pos = archivo.find(DELIMITADOR, pos);
	}

	// guardo string en el archivo
	unsigned int i = 0;
	while (i < archivo.size()) {
		file.put(archivo[i]);
		++i;
	}

	file.close();
}
