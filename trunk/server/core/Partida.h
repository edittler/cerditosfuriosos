#ifndef PARTIDA_H_
#define PARTIDA_H_

// C++ Library Includes.
#include <string>

enum EstadoPartida {
	CREANDO,
	EJECUTANDO,
	PAUSADO,
	FINALIZADO
};

class Partida {
public:
	Partida(unsigned int id, std::string nombre);
	virtual ~Partida();

	bool finalizo();

	EstadoPartida getEstado();

private:
	// ID de la partida
	unsigned int id;

	// Nombre de la partida.
	std::string nombre;

	// Estado de la partida
	EstadoPartida estado;

	// Ruta de archivo del mundo a correr
	// TODO Provisoriamente se va a usar para almacenar un nivel
	std::string rutaMundo;

	// Nivel que está corriendo la partida
//	nivel;
};

#endif /* PARTIDA_H_ */
