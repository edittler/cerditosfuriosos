#include "Juego.h"
#include "../vista/modelo/ConstantesVistaModelo.h"

#include <iostream> // FIXME eliminar
//#include <X11/Xlib.h>
#include <gtkmm/main.h>
#include <gtkmm/messagedialog.h>
#include "NivelLocal.h"

Juego::Juego(Escenario* escenario, VentanaCliente* ventana) {
//	XInitThreads();
	this->estado = SPLASH;
	this->nivel = new NivelLocal(escenario, 250);
	this->ventana = ventana;
}

Juego::~Juego() {
	delete this->nivel;
	delete this->vista;
}

void* Juego::run() {
	while (true) {
		switch (this->estado) {
			case SPLASH: {
				Gtk::Image imagen(SPLASH_IMAGEN);
				ventana->agregarContenedor(&imagen);
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
				ventana->agregarContenedor(vista);
				ventana->setMouseListener(new MouseListener(nivel->getEscenario()));

				int i = 0;
				while (!nivel->finalizoPartida()) {
					this->nivel->tick(20);
					std::cout << "tick " << i++ << std::endl;
					usleep(DELTA_LOOP);
				}
				this->estado = PERDIO;
				break; }
			case GANO: {
				this->estado = EXIT;
				break; }
			case PERDIO: {
				Gtk::Image imagen(GAME_OVER_IMAGEN);
				ventana->agregarContenedor(&imagen);
				sleep(WAIT);
				this->estado = EXIT;
				break; }
			case EXIT: {
				Gtk::MessageDialog m(*ventana, "Cerrando aplicacion.");
				ventana->agregarContenedor(&m);
				ventana->hide_all();
				break; }
			default:
				break;
		}
	}
	return NULL;
}
