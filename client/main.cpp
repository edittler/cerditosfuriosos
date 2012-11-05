/* Aplicación del cliente
 *
 */

// Standard C++ Library Includes.
#include <iostream>

// gtkmm Library Includes.
#include <gtkmm/main.h>

// Project Includes.
#include "vista/VentanaCliente.h"
#include "core/Client.h"

int main(int argc, char *argv[]) {
	Gtk::Main kit(argc, argv);
	VentanaCliente ventana;
	std::cout << "Soy el Cliente!!" << std::endl;

	Gtk::Main::run(ventana);
	return 0;
}

int main_core(int argc, char **argv) {

	Client* c = new Client("127.0.0.1", 5555);
	c->conectar();
	c->ejecutar();
	c->desconectar();
	delete c;
	return 0;
}



