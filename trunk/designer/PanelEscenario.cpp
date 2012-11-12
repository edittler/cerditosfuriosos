#include "PanelEscenario.h"

PanelEscenario::PanelEscenario() {
	lienzo = new Lienzo(800, 600);
	paletaEscenario = new PaletaEscenario();
	eliminador = new EliminadorPosicionables(lienzo);
	Gtk::VBox* cajaVertical = manage(new Gtk::VBox(false, 20));
	cajaVertical->pack_start(*paletaEscenario);
	cajaVertical->pack_start(*eliminador);
	Gtk::HBox* cajaHorizontal = manage(new Gtk::HBox(false, 20));
	cajaHorizontal->pack_start(*cajaVertical);
	cajaHorizontal->pack_start(*lienzo);
	add(*cajaHorizontal);
}

PanelEscenario::~PanelEscenario() {
	delete paletaEscenario;
	delete lienzo;
	delete eliminador;
}
