// Header Include.
#include "PanelMundo.h"

// Common Project Includes.
#include "XMLTypes.h"

// Designer Project Includes.
#include "CFDTools.h"
#include "ConstantesDiseniador.h"

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

	// Creo el nodo del nombre
	XMLNode* nodoNombre = new XMLNode("Nombre");
	XMLText* textNombre = new XMLText(creador->getNombreElegido());
	nodoNombre->LinkEndChild(textNombre);

	// Creo el nodo de la cantidad de jugadores
	XMLNode* nodoJugadores = new XMLNode("Jugadores");
	std::string sJugadores = cfd::intToString(creador->getCantidadJugadores());
	XMLText* textJugadores = new XMLText(sJugadores);
	nodoJugadores->LinkEndChild(textJugadores);

	// Creo el nodo de niveles vacío
	XMLNode* nodoNiveles = new XMLNode("Niveles");

	// Creo el nodo del mundo y linkeo los hijos
	XMLNode* nodoMundo = new XMLNode("Mundo");
	nodoMundo->LinkEndChild(nodoNombre);
	nodoMundo->LinkEndChild(nodoJugadores);
	nodoMundo->LinkEndChild(nodoNiveles);

	// Creo un Documento XML
	XMLDocument doc;
	XMLDeclaration* decl = new XMLDeclaration( "1.0", "UTF-8", "");
	doc.LinkEndChild(decl);
	doc.LinkEndChild(nodoMundo);

	// Establezco la ruta donde guardar el XML y lo guardo.
	std::string ruta = RUTA_CARPETA_MUNDOS + creador->getNombreElegido() + ".xml";
	doc.SaveFile(ruta);

	//Ahora procedo a editar el mundo recien creado
	informable->editarMundo(ruta);
}

void PanelMundo::cargarNombreMundos() {
	/*
	 * TODO Informacion para Eze:
	 * 
	 * Aca se deben cargar todos los mundos creados en el mapa "nombreMundos",
	 * que es atributo de este objeto. El mismo debe permitir acceder a la ruta
	 * del archivo de cada mundo a partir del nombre del mismo.
	 * 
	 * A continuacion hay un ejemplo hecho para que se pueda probar el codigo:
	 */
	nombreMundos[std::string("Mundo 1")] = std::string("mundo_1.xml");
	nombreMundos[std::string("Mundo 2")] = std::string("mundo_2.xml");
	nombreMundos[std::string("Mundo 3")] = std::string("mundo_3.xml");
}
