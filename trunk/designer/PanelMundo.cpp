#include "PanelMundo.h"

PanelMundo::PanelMundo() {
	cargarNombreMundos();
	// Widgets con funcionalidad
	botonEditar = new Gtk::Button("Editar mundo seleccionado");
	botonCrear = new Gtk::Button("Crear mundo nuevo");
	selector = new SelectorMundos(nombreMundos);
	creador = new CreadorMundo(nombreMundos);
	// Contenedores
	Gtk::VBox* cajaVertical = manage(new Gtk::VBox(true, 30));
	Gtk::HBox* cajaHorizontalUno = manage(new Gtk::HBox(false, 20));
	Gtk::HBox* cajaHorizontalDos = manage(new Gtk::HBox(false, 20));
	Gtk::Frame* cuadroEditar = manage(new Gtk::Frame(
												"Edite un mundo ya existente"));
	Gtk::Frame* cuadroCrear = manage(new Gtk::Frame("Cree un mundo nuevo"));
	cajaHorizontalUno->pack_start(*selector);
	Gtk::HButtonBox* cajaAuxiliarUno = manage(new Gtk::HButtonBox());
	cajaAuxiliarUno->set_layout(Gtk::BUTTONBOX_CENTER);
	cajaAuxiliarUno->pack_start(*botonEditar, Gtk::PACK_SHRINK);
	cajaHorizontalUno->pack_start(*cajaAuxiliarUno, Gtk::PACK_SHRINK);
	cajaHorizontalDos->pack_start(*creador);
	Gtk::HButtonBox* cajaAuxiliarDos = manage(new Gtk::HButtonBox());
	cajaAuxiliarDos->set_layout(Gtk::BUTTONBOX_CENTER);
	cajaAuxiliarDos->pack_start(*botonCrear, Gtk::PACK_SHRINK);
	cajaHorizontalDos->pack_start(*cajaAuxiliarDos, Gtk::PACK_SHRINK);
	cuadroEditar->add(*cajaHorizontalUno);
	cuadroCrear->add(*cajaHorizontalDos);
	cajaVertical->pack_start(*cuadroEditar);
	cajaVertical->pack_start(*cuadroCrear);
	add(*cajaVertical);
	// Seniales
	botonEditar->signal_clicked().connect(sigc::mem_fun(*this,
											&PanelMundo::botonEditarClickeado));
	botonCrear->signal_clicked().connect(sigc::mem_fun(*this,
											&PanelMundo::botonCrearClickeado));
}

PanelMundo::~PanelMundo() {
	delete botonEditar;
	delete botonCrear;
	delete selector;
	delete creador;
}

void PanelMundo::setInformable(InformableSeleccion* informable) {
	this->informable = informable;
}

void PanelMundo::botonEditarClickeado() {
	informable->editarMundo(selector->getNombreMundoSeleccionado());
}

void PanelMundo::botonCrearClickeado() {
	if (!(creador->nombreSeleccionadoValido()))
		informable->nombreSeleccionadoInvalido();
}

void PanelMundo::cargarNombreMundos() {
	nombreMundos[std::string("mundo_1.xml")] = std::string("Mundo uno");
	nombreMundos[std::string("mundo_2.xml")] = std::string("Mundo dos");
	nombreMundos[std::string("mundo_3.xml")] = std::string("Mundo tres");
}
