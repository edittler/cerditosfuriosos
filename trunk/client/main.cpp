/* Aplicación del cliente
 *
 */

// Standard C++ Library Includes.
#include <iostream>

// gtkmm Library Includes.
#include <gtkmm/main.h>

// Project Includes.
#include "vista/VentanaCliente.h"

int main(int argc, char *argv[]) {
	Gtk::Main kit(argc, argv);
	VentanaCliente ventana;
	std::cout << "Soy el Cliente!!" << std::endl;

	Gtk::Main::run(ventana);
	return 0;
}


