// Header Include.
#include "Juego.h"

// GTK+ Library Includes.
#include <gtkmm/main.h>
#include <gtkmm/messagedialog.h>

// Client Project Includes.
#include "../modelo/NivelLocal.h"
#include "../vista/modelo/ConstantesVistaModelo.h"

Juego::Juego(VentanaCliente* ventana) {
	this->ejecutando = true;
	this->nivel = new NivelLocal();
	this->ventana = ventana;
	this->vista = NULL;
	this->estado = SPLASH;
}

Juego::~Juego() {
	delete this->nivel;
	delete this->vista;
}

void Juego::finalizarJuego() {
	this->ejecutando = false;
}

void* Juego::run() {
	while (this->ejecutando) {
		switch (this->estado) {
			case SPLASH: {
				Gtk::Image imagen(SPLASH_IMAGEN);
				ventana->agregarContenedor(imagen);
				sleep(WAIT);
				this->estado = MENU;
			break; }
			case MENU: {
				this->estado = GAMEPLAY;
			break; }
			case GAMEPLAY: {
				// Creo la vista y le asocio el escenario del modelo
				this->vista = new VistaEscenario(nivel->getEscenario());

				// hidrato escenario
				this->nivel->cargarXML("../common/MiMundo-level1.xml");

				// Inicio la vista
				ventana->agregarContenedor(*vista);
				ventana->setMouseListener(new MouseListener(*nivel));

				int i = 0;
				while (!nivel->finalizoPartida() && this->ejecutando) {
					this->nivel->tick(TIEMPO_TICK_MSEG);
					std::cout << "tick " << i++ << std::endl;
					usleep(DELTA_LOOP);
				}

				if (nivel->getEscenario()->ganoPartida())
					this->estado = GANO;
				else
					this->estado = PERDIO;

				break; }
			case GANO: {
				Gtk::Image imagen(WIN_IMAGEN);
				ventana->agregarContenedor(imagen);
				sleep(WAIT);
				this->estado = EXIT;
				break; }
			case PERDIO: {
				Gtk::Image imagen(GAME_OVER_IMAGEN);
				ventana->agregarContenedor(imagen);
				sleep(WAIT);
				this->estado = EXIT;
				break; }
			case EXIT: {
				this->ejecutando = false;
				Gtk::Main::quit();
				break; }
			default:
				break;
		}
	}
	return NULL;
}
