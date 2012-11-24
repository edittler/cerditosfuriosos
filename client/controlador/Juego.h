#ifndef SIMULADORPROVISORIO_H_
#define SIMULADORPROVISORIO_H_

#include <unistd.h>

#include <../../common/thread/Thread.h>
#include <Escenario.h>
#include <Nivel.h>
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
	Juego(VentanaPrincipal* ventana);
	virtual ~Juego();

	void finalizarJuego();

	void* run();
private:

	void botonUnJugador();
	bool ejecutando;

	Nivel* nivel;

	VentanaPrincipal* ventana;
	VistaEscenario* vista;

	EstadosJuego estado;
};

#endif
