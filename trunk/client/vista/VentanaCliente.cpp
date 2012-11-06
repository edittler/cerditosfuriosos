// Header Include.
#include "VentanaCliente.h"

VentanaCliente::VentanaCliente() {
	set_title("Creador de niveles");
	set_border_width(10);
	set_resizable(false);

	show_all_children();
}

VentanaCliente::~VentanaCliente() {
	// TODO Auto-generated destructor stub
}

void VentanaCliente::agregarContenedor(Gtk::Container* conteiner) {
	this->add(*conteiner);
	show_all_children();
}

