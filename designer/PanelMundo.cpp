// Header Include.
#include "PanelMundo.h"

// Common Project Includes.
#include "XMLTypes.h"

// Designer Project Includes.
#include "CFDTools.h"
#include "ConstantesDiseniador.h"

// Constante de la ruta del archivo donde se almacenan todos los mundos
#define RUTA_MUNDOS "mundos.xml"

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
	Gtk::Frame* cuadroEditar = manage(new Gtk::Frame("Edite un mundo existente"));
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
	XMLDeclaration* decl = new XMLDeclaration("1.0", "UTF-8", "");
	doc.LinkEndChild(decl);
	doc.LinkEndChild(nodoMundo);

	// Establezco la ruta donde guardar el XML y lo guardo.
	std::string ruta = RUTA_CARPETA_MUNDOS + creador->getNombreElegido() + ".xml";
	doc.SaveFile(ruta);

	// Actualizo la lista de mundos
	this->actualizarArchivoMundos(ruta);

	// Ahora procedo a editar el mundo recien creado
	informable->editarMundo(ruta);
}

void PanelMundo::cargarNombreMundos() {
	/* En el directorio donde se encuentra el ejecutable, se almacenará un
	 * archivo donde se encuentran todos los mundos que ha creado el diseñador.
	 * Ese archivo se llamará "mundos.xml"
	 */
	XMLDocument doc;
	bool seAbrio = doc.LoadFile(RUTA_MUNDOS);
	// Si el archivo no existe, lo creo y salgo sin cargar mundos
	if (!seAbrio) {
		this->crearArchivoMundos();
		return;
	}

	// Obtengo el nodo raiz
	XMLNode* root = doc.RootElement();
	// Si es nulo, salgo sin realizar nada
	if (root == 0)
		return;

	// Obtengo el primer nodo del mundo
	const XMLNode* nodoMundo = root->FirstChildElement("Mundo");
	// Mientras el nodo de mundo no es nulo, cargo los mundos.
	while (nodoMundo != 0) {
		// Obtengo el nodo con el nombre del Mundo.
		const XMLNode* nodoNombre = nodoMundo->FirstChildElement("Nombre");
		std::string nombreMundo = nodoNombre->GetText();
		// Obtengo el atributo de la cantidad de jugadores
		int cantJugadores;
		const char* aCJ = nodoMundo->Attribute("cantJugadores", &cantJugadores);
		if (aCJ != 0) {
			std::string sCantJug = cfd::intToString(cantJugadores);
			nombreMundo += " (" + sCantJug;
			// Si la cantidad de jugadores es 1
			if (cantJugadores == 1) {
				nombreMundo += " jugador)";
			} else {
				nombreMundo += " jugadores)";
			}
		}
		// Obtengo el nodo con la ruta de archivo del mundo.
		const XMLNode* nodoRuta = nodoMundo->FirstChildElement("Ruta");
		// Si los nodos no son nulos, cargo el mundo a la tabla
		if ((nodoNombre != 0) && (nodoRuta != 0)) {
			nombreMundos[nombreMundo] = nodoRuta->GetText();
		}
		// Obtengo el siguiente nodo Mundo
		nodoMundo = nodoMundo->NextSiblingElement("Mundo");
	}
}

void PanelMundo::crearArchivoMundos() const {
	// Creo el nodo Mundos
	XMLNode* nodoMundos = new XMLNode("Mundos");
	// Creo un Documento y guardo el archivo.
	XMLDocument doc;
	XMLDeclaration* decl = new XMLDeclaration("1.0", "UTF-8", "");
	doc.LinkEndChild(decl);
	doc.LinkEndChild(nodoMundos);
	doc.SaveFile(RUTA_MUNDOS);
}

void PanelMundo::actualizarArchivoMundos(const std::string rutaMundo) const {
	// Abro el archivo de los mundos
	XMLDocument doc;
	bool seAbrio = doc.LoadFile(RUTA_MUNDOS);
	// Si el archivo no existe, salgo
	if (!seAbrio)
		return;

	// Obtengo el nodo raiz
	XMLNode* root = doc.RootElement();
	// Si es nulo, salgo sin realizar nada
	if (root == 0)
		return;

	// Creo el nodo asociado al mundo
	XMLNode* nodoMundo = new XMLNode("Mundo");
	// Agrego el atributo de la cantidad de jugadores
	nodoMundo->SetAttribute("cantJugadores", creador->getCantidadJugadores());

	// Creo el nodo asociado al nombre del mundo
	XMLNode* nodoNombre = new XMLNode("Nombre");
	XMLText* textNombre = new XMLText(creador->getNombreElegido());
	nodoNombre->LinkEndChild(textNombre);

	// Creo el nodo asociado a al ruta del archivo que almacena el mundo
	XMLNode* nodoRuta = new XMLNode("Ruta");
	XMLText* textRuta = new XMLText(rutaMundo);
	nodoRuta->LinkEndChild(textRuta);

	// Linkeo los nodos de nombre y ruta al del mundo
	nodoMundo->LinkEndChild(nodoNombre);
	nodoMundo->LinkEndChild(nodoRuta);

	// Linkeo el nodo del nuevo mundo al nodo de mundos
	root->LinkEndChild(nodoMundo);

	// Guardo el archivo
	doc.SaveFile();
}
