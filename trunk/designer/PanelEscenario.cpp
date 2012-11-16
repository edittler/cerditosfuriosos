#include "PanelEscenario.h"

PanelEscenario::PanelEscenario(std::string rutaNivel, InformableSeleccion* informable, int cantidadJugadores) {
	this->cantidadJugadores = cantidadJugadores;
	this->informable = informable;
	this->rutaNivel = rutaNivel;
	lienzo = new Lienzo(800, 600, cantidadJugadores);
	paletaEscenario = new PaletaEscenario();
	eliminador = new EliminadorPosicionables(lienzo);
	entrada = new EntradaPajaros(800, 600);
	botonGuardar = new Gtk::Button();
	Gtk::Image* imagenGuardar = manage(new Gtk::Image(
			Gtk::StockID("gtk-floppy"), Gtk::IconSize(Gtk::ICON_SIZE_BUTTON)));
	botonGuardar->set_image(*imagenGuardar);
	Gtk::VBox* cajaVerticalUno = manage(new Gtk::VBox(false, 20));
	cajaVerticalUno->pack_start(*paletaEscenario);
	cajaVerticalUno->pack_start(*eliminador);
	Gtk::HButtonBox* cajaAuxiliarUno = manage(new Gtk::HButtonBox());
	cajaAuxiliarUno->set_layout(Gtk::BUTTONBOX_CENTER);
	cajaAuxiliarUno->pack_start(*botonGuardar, Gtk::PACK_SHRINK);
	Gtk::HBox* cajaHorizontalUno = manage(new Gtk::HBox(false, 20));
	Gtk::Label* etiquetaGuardar = manage(new Gtk::Label("Guardar nivel: "));
	cajaHorizontalUno->pack_start(*etiquetaGuardar);
	cajaHorizontalUno->pack_start(*cajaAuxiliarUno);
	Gtk::VBox* cajaVerticalDos = manage(new Gtk::VBox(false, 20));
	cajaVerticalDos->pack_start(*entrada);
	cajaVerticalDos->pack_start(*cajaHorizontalUno);
	Gtk::HBox* cajaHorizontal = manage(new Gtk::HBox(false, 20));
	cajaHorizontal->pack_start(*cajaVerticalUno);
	cajaHorizontal->pack_start(*lienzo);
	cajaHorizontal->pack_start(*cajaVerticalDos);
	add(*cajaHorizontal);
	// Seniales
	botonGuardar->signal_clicked().connect(sigc::mem_fun(*this,
									&PanelEscenario::botonGuardarClickeado));
}

PanelEscenario::~PanelEscenario() {
	delete paletaEscenario;
	delete lienzo;
	delete eliminador;
	delete entrada;
	delete botonGuardar;
}

void PanelEscenario::botonGuardarClickeado() {
	bool escenarioValido = true;
	std::string mensaje("Antes de poder guardar debe realizar las siguientes correciones:\n");
	if (!(entrada->lineaEntradaValida())) {
		escenarioValido = false;
		mensaje += "- La línea de entrada de pajaros no tiene puntos de inicio y fin válidos\n";
	}
	if (!(entrada->porcentajesPajarosValidos())) {
		escenarioValido = false;
		mensaje += "- Los porcentajes de aparición de los pájaros no suman 100%\n";
	}
	if (!(lienzo->cantidadJugadoresValida())) {
		escenarioValido = false;
		mensaje += "- El numero de jugadores debe ser";
		mensaje += (char)(cantidadJugadores + '0');
		mensaje += "\n";
	}
	if (!(lienzo->objetosJugadoresCorrectos())) {
		escenarioValido = false;
		mensaje += "- Debe haber una catapulta y un montículo por cada cerdo\n";
	}
	if (!escenarioValido) {
		informable->mostrarDialogo(mensaje);
		return;
	}
}
