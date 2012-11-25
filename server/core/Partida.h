#ifndef PARTIDA_H_
#define PARTIDA_H_

#include "../modelo/NivelServer.h"

// C++ Library Includes.
#include <string>

enum EstadoPartida {
	CREANDO,
	EJECUTANDO,
	ESPERANDO_JUGADOR,
	PAUSADO,
	FINALIZADO
};

class Partida {
public:
	Partida(unsigned int id, std::string nombre);
	virtual ~Partida();

	/*
	 * @brief valida que la partida pueda comenzar a ejecutarse
	 * @return true si se puede, false caso contrario.
	 */
	bool comienzo();

	/*
	 * @brief valida que la partida haya finalizado.
	 * @return true si finalizo, false caso contrario.
	 */
	bool finalizo();

	void setRutaMundo(std::string path);

	void cargarSiguienteNivel();

	/*
	 * @brief devuelve el id del primer jugador que se encuentro
	 * no conectado hacia un cliente.
	 * @return id del jugador, en caso de que todos los jugadores
	 * se encuentren conectados devuelve 0.
	 */
	unsigned int getIdJugadorNoConectado();

	/*
	 * @brief setea como no conectado a un jugador del escenario.
	 * @param id del jugador a desconectar
	 */
	void setIdJugadorNoConectado(unsigned int id);

	EstadoPartida getEstado();
	void setEstado(EstadoPartida estado);

	unsigned int getId();
	static unsigned int generarId();

	std::string getNombre() const;

	/*
	 * @brief carga todos los niveles correspondientes al mundo
	 * indicado en this->rutaMundo.
	 */
	void cargarNiveles();

private:

	// generador de ids.
	static unsigned int proximoId;

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
	NivelServer* nivel;

	// mapa con path de niveles
	std::map<int, std::string> idNiveles;

	// contador de niveles
	unsigned int contadorNiveles;
};

#endif /* PARTIDA_H_ */
