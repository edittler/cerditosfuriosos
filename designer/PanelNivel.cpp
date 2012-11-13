#include "PanelNivel.h"

PanelNivel::PanelNivel(std::string rutaMundo, InformableSeleccion* informable) {
	this->informable = informable;
	cargarIdNiveles(rutaMundo);
	// Cargo el selector
	Gtk::HBox* cajaHorizontalUno = manage(new Gtk::HBox(false, 20));
	selector = new SelectorNiveles(idNiveles);
	cajaHorizontalUno->pack_start(*selector);
	botonEditar = new Gtk::Button("Editar nivel seleccionado");
	Gtk::HButtonBox* cajaAuxiliarUno = manage(new Gtk::HButtonBox());
	cajaAuxiliarUno->set_layout(Gtk::BUTTONBOX_CENTER);
	cajaAuxiliarUno->pack_start(*botonEditar, Gtk::PACK_SHRINK);
	cajaHorizontalUno->pack_start(*cajaAuxiliarUno, Gtk::PACK_SHRINK);
	Gtk::Frame* cuadroEditar = manage(new Gtk::Frame("Edite un nivel ya existente"));
	cuadroEditar->add(*cajaHorizontalUno);
	// Cargo el creador
	Gtk::HBox* cajaHorizontalDos = manage(new Gtk::HBox(false, 20));
	creador = new CreadorNivel(idNiveles.size()+1, informable);
	cajaHorizontalDos->pack_start(*creador);
	botonCrear = new Gtk::Button("Crear nivel nuevo");
	Gtk::HButtonBox* cajaAuxiliarDos = manage(new Gtk::HButtonBox());
	cajaAuxiliarDos->set_layout(Gtk::BUTTONBOX_CENTER);
	cajaAuxiliarDos->pack_start(*botonCrear, Gtk::PACK_SHRINK);
	cajaHorizontalDos->pack_start(*cajaAuxiliarDos, Gtk::PACK_SHRINK);
	Gtk::Frame* cuadroCrear = manage(new Gtk::Frame("Cree un nuevo nivel"));
	cuadroCrear->add(*cajaHorizontalDos);
	// Cargo en el contenedor
	Gtk::VBox* cajaVertical = manage(new Gtk::VBox(false, 30));
	cajaVertical->pack_start(*cuadroEditar);
	cajaVertical->pack_start(*cuadroCrear);
	add(*cajaVertical);
	// Seniales
	botonCrear->signal_clicked().connect(sigc::mem_fun(*this,
											&PanelNivel::botonCrearClickeado));
}

PanelNivel::~PanelNivel() {
	delete selector;
	delete creador;
	delete botonEditar;
	delete botonCrear;
}

void PanelNivel::botonCrearClickeado() {
	informable->crearNivel();
}

void PanelNivel::cargarIdNiveles(std::string rutaMundo) {
	idNiveles[std::string("nivel_1.xml")] = 1;
	idNiveles[std::string("nivel_2.xml")] = 2;
	idNiveles[std::string("nivel_3.xml")] = 3;
}
