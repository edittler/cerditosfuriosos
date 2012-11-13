#include "CreadorNivel.h"

CreadorNivel::CreadorNivel(int idProximoNivel, InformableSeleccion* informable) {
	this->idProximoNivel = idProximoNivel;
	this->informable = informable;
	// Widgets con funcionalidad
	Gtk::Label* etiquetaTamanio = manage(new Gtk::Label(
							"Seleccione el tamaño que tendra el escenario: "));
	Gtk::Label* etiquetaDuracion = manage(new Gtk::Label(
							"Seleccione la duración del nivel (en segundos): "));
	selectorTamanio.append_text("Chico");
	selectorTamanio.append_text("Mediano");
	selectorTamanio.append_text("Grande");
	selectorTamanio.set_active_text("Mediano");
	ajuste = new Gtk::Adjustment(1.0, 15.0, 60.0);
	selectorDuracion = new Gtk::SpinButton(*ajuste);
	selectorDuracion->set_editable(false);
	archivoImagen = new Gtk::Entry();
	archivoImagen->set_editable(false);
	botonExaminar = new Gtk::Button("Examinar...");
	// Contenedores
	Gtk::HBox* cajaHorizontalUno = manage(new Gtk::HBox(false, 20));
	cajaHorizontalUno->pack_start(*etiquetaTamanio);
	cajaHorizontalUno->pack_start(selectorTamanio);
	Gtk::HBox* cajaHorizontalDos = manage(new Gtk::HBox(false, 20));
	cajaHorizontalDos->pack_start(*etiquetaDuracion);
	cajaHorizontalDos->pack_start(*selectorDuracion);
	Gtk::HBox* cajaHorizontalTres = manage(new Gtk::HBox(false, 20));
	cajaHorizontalTres->pack_start(*archivoImagen);
	cajaHorizontalTres->pack_start(*botonExaminar);
	Gtk::VBox* cajaVertical = manage(new Gtk::VBox(false, 30));
	cajaVertical->pack_start(*cajaHorizontalUno);
	cajaVertical->pack_start(*cajaHorizontalDos);
	cajaVertical->pack_start(*cajaHorizontalTres);
	add(*cajaVertical);
	// Seniales
	botonExaminar->signal_clicked().connect(sigc::mem_fun(*this,
										&CreadorNivel::botonExaminarClickeado));
}

CreadorNivel::~CreadorNivel() {
	delete ajuste;
	delete selectorDuracion;
	delete archivoImagen;
	delete botonExaminar;
}

void CreadorNivel::botonExaminarClickeado() {
	std::string nombreArchivo = informable->seleccionarImagen();
	archivoImagen->set_text(nombreArchivo);
}
