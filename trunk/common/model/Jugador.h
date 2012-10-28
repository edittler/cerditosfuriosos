#ifndef JUGADOR_H_
#define JUGADOR_H_

//Project Includes.
#include "Cerdito.h"
#include "Puntaje.h"

/* Clase Jugador que contiene los datos necesarios para el juego
 * Cerditos Furiosos.
 */
class Jugador {
public:
	/* Constructor que recibe el cerdito asociado
	 */
	explicit Jugador(Cerdito* cerdito);

	virtual ~Jugador();

	/* Suma los puntos especificados.
	 * @param puntos a incrementar en el jugador.
	 */
	void sumarPuntos(int puntos);

private:
	// Cerdito asociado al jugador
	Cerdito* cerdito;

	// Puntaje del jugador
	Puntaje puntaje;
};

#endif /* JUGADOR_H_ */
