// Header Include.
#include "VentanaCliente.h"
#include "../controlador/MouseListener.h" // FIXME borrar

VentanaCliente::VentanaCliente() {
	set_title("Cerditos Furiosos");
	set_border_width(10);
	set_resizable(false);

	this->contenedor = new Gtk::EventBox();
	this->add(*contenedor);

	show_all_children();
}

VentanaCliente::~VentanaCliente() {
	delete contenedor;
}

void VentanaCliente::agregarContenedor(Gtk::Widget* widget) {
	// elimina widget anterior
	contenedor->remove();
	// agrega widget nuevo.
	contenedor->add(*widget);

	show_all_children();
}

void VentanaCliente::setMouseListener(MouseListener* listener) {
	listener->cargarEventos(contenedor);
}
