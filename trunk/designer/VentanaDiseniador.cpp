#include "VentanaDiseniador.h"

VentanaDiseniador::VentanaDiseniador() {
	set_title("Creador de niveles");
	set_border_width(10);
	set_resizable(false);
	panelMundo = new PanelMundo();
	add(*panelMundo);
	panelMundo->setInformable(this);
	panelNivel = NULL;
	panelEscenario = NULL;
	show_all_children();
}

VentanaDiseniador::~VentanaDiseniador() {
	delete panelMundo;
	if (panelNivel != NULL)
		delete panelNivel;
	if (panelEscenario != NULL)
		delete panelEscenario;
}

void VentanaDiseniador::editarMundo(std::string rutaMundo) {
	remove();
	panelNivel = new PanelNivel(rutaMundo, this);
	add(*panelNivel);
	show_all_children();
}

void VentanaDiseniador::nombreSeleccionadoInvalido() {
	Gtk::MessageDialog dialogo(*this, "Nombre invalido");
	dialogo.run();
}

void VentanaDiseniador::crearNivel() {
	remove();
	panelEscenario = new PanelEscenario();
	add(*panelEscenario);
	show_all_children();
}

std::string VentanaDiseniador::seleccionarImagen() {
	Gtk::FileChooserDialog dialogo("Seleccione una imagen", 
												Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialogo.set_transient_for(*this);
	dialogo.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialogo.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
	Gtk::FileFilter filtroImagenes;
	filtroImagenes.set_name("Imagenes");
	filtroImagenes.add_mime_type("image/*");
	dialogo.add_filter(filtroImagenes);
	int resultado = dialogo.run();
	if (resultado == Gtk::RESPONSE_OK)
		return dialogo.get_filename();
	std::string noSeleccion("");
	return noSeleccion;
}
