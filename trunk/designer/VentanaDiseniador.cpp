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
	panelNivel = new PanelNivel(rutaMundo);
	panelNivel->setInformable(this);
	add(*panelNivel);
	show_all_children();
}

void VentanaDiseniador::nombreSeleccionadoInvalido() {
	Gtk::MessageDialog dialog(*this, "Nombre invalido");
	dialog.run();
}

void VentanaDiseniador::crearNivel() {
	remove();
	panelEscenario = new PanelEscenario();
	add(*panelEscenario);
	show_all_children();
}
