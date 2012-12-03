#include "VentanaDiseniador.h"

VentanaDiseniador::VentanaDiseniador() {
	set_title("Creador de niveles");
	set_border_width(10);
	set_resizable(false);
	set_position(Gtk::WIN_POS_CENTER_ALWAYS);
	panelMundo = new PanelMundo();
	add(*panelMundo);
	panelMundo->setInformable(this);
	panelNivel = NULL;
	panelEscenario = NULL;
	this->signal_delete_event().connect(sigc::mem_fun(*this,
                                        &VentanaDiseniador::cerrarVentana));
	show_all_children();
}

VentanaDiseniador::~VentanaDiseniador() {
	delete panelMundo;
	if (panelNivel != NULL)
		delete panelNivel;
	if (panelEscenario != NULL)
		delete panelEscenario;
}

void VentanaDiseniador::volverAPanelMundos() {
	delete panelMundo;
	delete panelNivel;
	if (panelEscenario != NULL)
		delete panelEscenario;
	panelMundo = new PanelMundo();
	add(*panelMundo);
	panelMundo->setInformable(this);
	panelNivel = NULL;
	panelEscenario = NULL;
	show_all_children();
}

void VentanaDiseniador::editarMundo(std::string rutaMundo) {
	remove();
	panelNivel = new PanelNivel(rutaMundo, this);
	add(*panelNivel);
	show_all_children();
}

void VentanaDiseniador::nombreSeleccionadoVacio() {
	Gtk::MessageDialog dialogo(*this, "Por favor elija un nombre para el mundo");
	dialogo.run();
}
		
void VentanaDiseniador::nombreSeleccionadoYaExistente() {
	Gtk::MessageDialog dialogo(*this, "El nombre elegido para el mundo ya "
			"pertenece a otro, por favor elija uno nuevo");
	dialogo.run();
}

void VentanaDiseniador::editarNivel(std::string rutaNivel, bool nivelNuevo) {
	remove();
	panelEscenario = new PanelEscenario(rutaNivel, this,
								panelNivel->getCantidadJugadores(), nivelNuevo);
	add(*panelEscenario);
	show_all_children();
}


std::string VentanaDiseniador::seleccionarImagen() {
	/*Gtk::FileChooserDialog dialogo("Seleccione una imagen", 
												Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialogo.set_transient_for(*this);
	dialogo.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialogo.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
	dialogo.set_current_folder(RUTA_FONDOS);
	Gtk::FileFilter filtroImagenes;
	filtroImagenes.set_name("Imagenes");
	filtroImagenes.add_mime_type("image/     *");
	dialogo.add_filter(filtroImagenes);
	int resultado = dialogo.run();
	std::string seleccion("");
	if (resultado == Gtk::RESPONSE_OK) {
		seleccion = dialogo.get_filename();
		seleccion = seleccion.substr(seleccion.find_last_of('/')+1,
				seleccion.size()-seleccion.find_last_of('/')-1);
	}
	return seleccion;*/
	SelectorImagenFondo dialogo;
	dialogo.set_transient_for(*this);
	dialogo.cargarComponentes();
	int resultado = dialogo.run();
	if (resultado == Gtk::RESPONSE_OK)
		return dialogo.getNombreArchivo();
	return "";
}

void VentanaDiseniador::mostrarDialogo(std::string mensaje) {
	Gtk::MessageDialog dialogo(*this, mensaje);
	dialogo.run();
}

void VentanaDiseniador::imagenNoSeleccionadaFondo() {
	Gtk::MessageDialog dialogo(*this, "Por favor seleccione una imagen para el "
			"fondo del escenario");
	dialogo.run();
}

void VentanaDiseniador::imagenNoSeleccionadaSuelo() {
	Gtk::MessageDialog dialogo(*this, "Por favor seleccione una imagen para el "
			"suelo del escenario");
	dialogo.run();
}

bool VentanaDiseniador::cerrarVentana(GdkEventAny* event) {
	if (get_child() == panelEscenario) {
		if (!panelEscenario->escenarioValido())
			return true;
		panelEscenario->guardarNivel();
	}
	return on_delete_event(event);
}
