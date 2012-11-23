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
#include "Escenario.h"
#include "controlador/Juego.h"
#include "controlador/MouseListener.h"
#include "vista/modelo/ConstantesVistaModelo.h"
#include "vista/menues/VentanaPrincipal.h"


int main(int argc, char *argv[]) {
	Gtk::Main kit(argc, argv);
	VentanaCliente ventana;

	Juego juego(&ventana);
	juego.start();

	Gtk::Main::run(ventana);

	juego.finalizarJuego();
	juego.join();
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

int maingtk(int argc, char *argv[]) {
  Gtk::Main kit(argc, argv);

  VentanaPrincipal ventana;
  Gtk::Main::run(ventana);
  return 0;
}


