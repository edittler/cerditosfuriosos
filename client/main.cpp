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
#include "vista/modelo/SimuladorProvisorio.h"

int main(int argc, char *argv[]) {
	Gtk::Main kit(argc, argv);
	VentanaCliente ventana;

	Escenario* escenario = new Escenario();
	escenario->setAncho(1024);
	escenario->setAlto(640);

	VistaEscenario* vEscenario = new VistaEscenario(escenario);
	ventana.agregarContenedor(vEscenario);

	std::cout << "Soy el Cliente!!" << std::endl;

	escenario->agregarCerdito(Punto2D(0.2, 1), Punto2D(10, 10));
	escenario->agregarMonticulo(Punto2D(1,1));
	escenario->habilitarSimulacion();
	escenario->lanzarPajaroRojo(Punto2D(10,5), Velocidad2D(-10, -5));

	SimuladorProvisorio sim(escenario);

	sim.start();

	Gtk::Main::run(ventana);

	sim.join();
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



