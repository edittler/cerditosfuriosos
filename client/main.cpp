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

	Escenario escenario;
	// FIXME el alto y ancho del escenario deberia setearse en metros (mundo Box2D)
	// y dentro del constructor de VistaEscenario aplicarse el escalado realizando
	// la multiplicacion por AJUSTE_ESCALA_VISTA
	escenario.setAncho(20);
	escenario.setAlto(12);

	VistaEscenario vEscenario(&escenario);
	ventana.agregarContenedor(&vEscenario);

	std::cout << "Soy el Cliente!!" << std::endl;

	escenario.agregarCerdito(Punto2D(0.4, 0.6), Punto2D(10, 10));
	escenario.agregarMonticulo(Punto2D(-1,-1));
	escenario.agregarCajaMadera(Punto2D(5,3));
	escenario.habilitarSimulacion();
	escenario.lanzarPajaroRojo(Punto2D(6*2,6), Velocidad2D(-5, 5));
	escenario.lanzarPajaroRojo(Punto2D(8*2,6), Velocidad2D(-5, -5));
	escenario.lanzarPajaroRojo(Punto2D(9*2,7), Velocidad2D(-10, 0));
	escenario.lanzarPajaroRojo(Punto2D(7*2,4), Velocidad2D(-12, 1));
	escenario.lanzarPajaroRojo(Punto2D(4*2,5), Velocidad2D(-2, 9));
	escenario.lanzarHuevoBlanco(Punto2D(1,1), Velocidad2D(5.5, 13));

	SimuladorProvisorio sim(&escenario);

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



