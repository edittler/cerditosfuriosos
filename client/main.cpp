/* Aplicación del cliente
 *
 */

// Standard C++ Library Includes.
#include <iostream>

// gtkmm Library Includes.
#include <gtkmm/main.h>

// Project Includes.
#include "vista/VentanaCliente.h"
#include "vista/modelo/VistaEscenario.h"
#include "core/Client.h"
#include "../../common/model/Escenario.h"

int main(int argc, char *argv[]) {
	Gtk::Main kit(argc, argv);
	VentanaCliente ventana;

	Escenario* escenario = new Escenario();
	escenario->setAncho(1024);
	escenario->setAlto(640);

	VistaEscenario* vEscenario = new VistaEscenario(escenario);
	ventana.agregarContenedor(vEscenario);

	std::cout << "Soy el Cliente!!" << std::endl;

	Gtk::Main::run(ventana);

	escenario->agregarCerdito(Punto2D(3, 10), Punto2D(10, 10));

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



