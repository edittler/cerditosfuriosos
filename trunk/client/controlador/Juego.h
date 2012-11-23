#ifndef SIMULADORPROVISORIO_H_
#define SIMULADORPROVISORIO_H_

#include <unistd.h>

#include <../../common/thread/Thread.h>
#include <Escenario.h>
#include <Nivel.h>
#include "../vista/VentanaCliente.h"
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
	Juego(VentanaCliente* ventana);
	virtual ~Juego();

	void finalizarJuego();

	void* run();
private:
	bool ejecutando;

	Nivel* nivel;

	VentanaCliente* ventana;
	VistaEscenario* vista;

	EstadosJuego estado;
};

#endif
