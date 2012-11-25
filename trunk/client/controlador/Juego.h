#ifndef JUEGO_H_
#define JUEGO_H_

// Common Project Includes.
#include "../../common/thread/Thread.h"
#include "../../common/model/Nivel.h"

// Client Project Includes.
#include "../core/Client.h"
#include "../vista/menues/VentanaPrincipal.h"
#include "../vista/modelo/VistaEscenario.h"

enum EstadosJuego {
	SPLASH,
	MENU,
	GAMEPLAY,
	GANO,
	PERDIO,
	EXIT
};

class Juego: public Thread {
public:
	/**
	 * Constructor
	 * @param ventana que manipula el juego para visualizarse.
	 */
	Juego(VentanaPrincipal& ventana);

	/**
	 * Destructor
	 */
	virtual ~Juego();

	/**
	 * Finaliza la ejecución del juego
	 */
	void finalizarJuego();

protected:
	/**
	 * Metodo que contiene la funcionalidad que ejecuta el thread del juego
	 */
	void* run();

private:
	void inicialSenialesBotones();

	void botonUnJugador();

	void botonMultijugador();

	void botonSalir();

	// Booleano que especifica si el juego se está ejecutando.
	bool ejecutando;

	/* bool que especifica si se está corriendo un juego local o remoto
	 * (multijugador).
	 */
	bool local;

	// Ventana que tiene asociado el juego.
	VentanaPrincipal& ventana;

	// Nivel que está ejecutando el juego.
	Nivel* nivel;

	// Vista del escenario asociado al nivel que está corriendo el juego.
	VistaEscenario* vista;

	// Estado del juego.
	EstadosJuego estado;
};

#endif
