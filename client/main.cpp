/* Aplicación del cliente
 *
 */

// Standard C++ Library Includes.
#include <iostream>

// gtkmm Library Includes.
#include <gtkmm/main.h>

// Project Includes.
#include "core/Client.h"
#include "controlador/Juego.h"
#include "vista/menues/VentanaPrincipal.h"

int main(int argc, char *argv[]) {
	Gtk::Main kit(argc, argv);
	VentanaPrincipal ventana;

	Juego juego(ventana);
	juego.start();

	Gtk::Main::run(ventana);

	juego.finalizarJuego();
	juego.join();
	return 0;
}
