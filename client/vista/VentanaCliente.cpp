// Header Include.
#include "VentanaCliente.h"
#include "modelo/ConstantesVistaModelo.h"

VentanaCliente::VentanaCliente() {
	set_title("Cerditos Furiosos");
	set_resizable(false);
	set_default_size(VENTANA_WIDTH, VENTANA_HEIGHT);

	// posiciono ventana en medio de la pantalla
	set_position(Gtk::WIN_POS_CENTER_ALWAYS);

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
	// FIXME guardar referencia l listener para despues poder liberar memoria.
	listener->cargarEventos(contenedor);
}
