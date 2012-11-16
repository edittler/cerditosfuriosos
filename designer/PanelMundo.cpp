#include "PanelMundo.h"

PanelMundo::PanelMundo() {
	set_size_request(600, 400);
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
	if (nombreMundos.size() > 0)
		informable->editarMundo(selector->getRutaMundoSeleccionado());
}

void PanelMundo::botonCrearClickeado() {
	if (creador->nombreVacio()) {
		informable->nombreSeleccionadoVacio();
		return;
	}
	if (creador->nombreExistente()) {
		informable->nombreSeleccionadoYaExistente();
		return;
	}
	/*
	 * Informacion para Eze: Aca se debe crear un nuevo mundo. Llamando a:
	 * - creador->getNombreElegido(): Se obtiene un string con el nombre del
	 * mundo seleccionado por el usuario (ya validado mas arriba en este metodo)
	 * - creador->getCantidadJugadores(): Se obtiene un entero con la cantidad
	 * de jugadores que el usuario selecciono para el mundo.
	 * Una vez que se creo el archivo, hay que enviar el siguiente mensaje:
	 * - informable->editarMundo(PARAMETRO)
	 * El parametro debe ser la ruta del archivo creado.
	 */ 
}

void PanelMundo::cargarNombreMundos() {
	/*
	 * Informacion para Eze: Aca se deben cargar todos los mundos creados en un
	 * mapa stl, el cual debe permitir acceder a la ruta del archivo de cada
	 * mundo a partir del nombre del mismo.
	 * 
	 * A continuacion hay un ejemplo hecho para que se pueda probar el codigo:
	 * 
	 * 
	 */
	nombreMundos[std::string("Mundo 1")] = std::string("mundo_1.xml");
	nombreMundos[std::string("Mundo 2")] = std::string("mundo_2.xml");
	nombreMundos[std::string("Mundo 3")] = std::string("mundo_3.xml");
}
