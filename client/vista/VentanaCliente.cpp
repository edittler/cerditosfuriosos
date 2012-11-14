// Header Include.
#include "VentanaCliente.h"
#include "modelo/ConstantesVistaModelo.h"

VentanaCliente::VentanaCliente() {
	set_title("Cerditos Furiosos");
	set_resizable(false);
	set_default_size(VENTANA_WIDTH, VENTANA_HEIGHT);

	// Inicializa multi threading
	gdk_threads_init();

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
	gdk_threads_enter();
		// elimina widget anterior
		contenedor->remove();
		// agrega widget nuevo.
		contenedor->add(*widget);

		show_all_children();
	gdk_threads_leave();
}

void VentanaCliente::setMouseListener(MouseListener* listener) {
	// FIXME guardar referencia l listener para despues poder liberar memoria.
	gdk_threads_enter();
		listener->cargarEventos(contenedor);
	gdk_threads_leave();
}
