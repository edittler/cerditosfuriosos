#include "PanelConfiguracion.h"

#include <gtkmm/label.h>

PanelConfiguracion::PanelConfiguracion(int ancho, int alto, string ruta,
		InterfazSelectora* interfaz) : PanelImagenFondo(ancho, alto, ruta) {
	this->interfaz = interfaz;

	// Inicializo el campo de Direccion IP
	direccion = new Gtk::Entry();
//	Glib::ustring usDireccion();
	direccion->set_text(DIRECCION_DEFAULT);
	direccion->set_size_request(ANCHO_DIRECCION, ALTO_DIRECCION);
	Gtk::Label* etiquetaDireccion = manage(new Gtk::Label("Direccion IP"));
	put(*direccion, X_DIRECCION, Y_DIRECCION);
	put(*etiquetaDireccion, X_ETIQUETA_DIRECCION, Y_ETIQUETA_DIRECCION);

	// Inicializo el campo de Puerto
	Gtk::Adjustment* ajustePuerto = manage(new Gtk::Adjustment(
			PUERTO_VALOR_DEFAULT, PUERTO_MINIMO, PUERTO_MAXIMO));
	puerto = new Gtk::SpinButton(*ajustePuerto);
	Gtk::Label* etiquetaPuerto = manage(new Gtk::Label("Puerto"));
	put(*puerto, X_PUERTO, Y_PUERTO);
	put(*etiquetaPuerto, X_ETIQUETA_PUERTO, Y_ETIQUETA_PUERTO);

	// Inicializo el boton de guardar
	botonGuardar = new Gtk::Button("Guardar");
	botonGuardar->set_size_request(ANCHO_BOTON_GUARGAR_CONFIGURACION,
			ALTO_BOTON_GUARGAR_CONFIGURACION);
	put(*botonGuardar, X_BOTON_GUARGAR_CONFIGURACION,
			Y_BOTON_GUARGAR_CONFIGURACION);

	// Inicializo el boton de volver
	botonVolver = new Gtk::Button("Volver al menu principal");
	put(*botonVolver, X_BOTON_VOLVER_CONFIGURACION, Y_BOTON_VOLVER_CONFIGURACION);

	// Conecto señales
	botonVolver->signal_clicked().connect(sigc::mem_fun(*this,
			&PanelConfiguracion::botonVolverClickeado));
}

PanelConfiguracion::~PanelConfiguracion() {
	delete direccion;
	delete puerto;
	delete botonGuardar;
	delete botonVolver;
}

void PanelConfiguracion::setearValores(const std::string direccion,
		const unsigned short int puerto) {
//	Glib::ustring usDireccion(direccion);
	this->direccion->set_text(direccion);
	if ((puerto > PUERTO_MINIMO) && (puerto < PUERTO_MAXIMO))
		this->puerto->set_value((double) puerto);
}

std::string PanelConfiguracion::getDireccion() const {
	return this->direccion->get_text();
}

unsigned short int PanelConfiguracion::getPuerto() const {
	unsigned short int port = this->puerto->get_value_as_int();
	return port;
}

void PanelConfiguracion::botonVolverClickeado() {
	this->interfaz->volverAMenuPrincipal();
}
