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
//	int ancho = 14, alto = 6; 	// setear AJUSTE_ESCALA_VISTA = 80
//	int ancho = 16, alto = 8; 	// setear AJUSTE_ESCALA_VISTA = 70
//	int ancho = 18, alto = 10; 	// setear AJUSTE_ESCALA_VISTA = 60
	int ancho = 20, alto = 12;  // setear AJUSTE_ESCALA_VISTA = 50
	escenario.setAncho(ancho);
	escenario.setAlto(alto);

	VistaEscenario vEscenario(&escenario);
	ventana.agregarContenedor(&vEscenario);

	std::cout << "Soy el Cliente!!" << std::endl;

	escenario.agregarCerdito(Punto2D(0.4, 0.6), Punto2D(10, 10));
	escenario.agregarMonticulo(Punto2D(-1,-1));
	escenario.agregarCajaMadera(Punto2D(5,3));
	escenario.habilitarSimulacion();
	escenario.lanzarPajaroRojo(Punto2D(ancho - 2, alto - 4), Velocidad2D(-5, 5));
	escenario.lanzarPajaroRojo(Punto2D(ancho - 3, alto - 4), Velocidad2D(-5, -5));
	escenario.lanzarPajaroRojo(Punto2D(ancho - 3, alto - 2), Velocidad2D(-10, 0));
	escenario.lanzarPajaroRojo(Punto2D(ancho - 1, alto - 4), Velocidad2D(-12, 1));
	escenario.lanzarPajaroRojo(Punto2D(ancho - 5, 2), Velocidad2D(-4, 9));
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



