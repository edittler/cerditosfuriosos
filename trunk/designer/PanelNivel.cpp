#include "PanelNivel.h"

PanelNivel::PanelNivel(std::string rutaMundo, InformableSeleccion* informable) {
	set_size_request(600, 400);
	this->rutaMundo = rutaMundo;
	this->informable = informable;
	cargarNiveles(rutaMundo);
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
	botonEditar->signal_clicked().connect(sigc::mem_fun(*this,
											&PanelNivel::botonEditarClickeado));
}

PanelNivel::~PanelNivel() {
	delete selector;
	delete creador;
	delete botonEditar;
	delete botonCrear;
}

void PanelNivel::botonEditarClickeado() {
	if (idNiveles.size() > 0)
		informable->editarNivel(selector->getRutaNivelSeleccionado(), false);
}

void PanelNivel::botonCrearClickeado() {
	if (!(creador->imagenSeleccionada())) {
		informable->imagenNoSeleccionada();
		return;
	}
	/* 
	 * Informacion para Eze:
	 * 
	 * Aca hay que crear el archivo de un nivel.
	 * 
	 * Para agregarlo al mundo que lo contiene contas con la ruta del archivo
	 * del mundo en el atributo "rutaMundo" de este objeto.
	 * 
	 * Para obtener el id del nivel en cuestion, podes preguntarle por el size
	 * al mapa "idNiveles" y sumarle uno, dado que ahi tenes todos los niveles
	 * del mundo sobre el que se esta trabajando.
	 * 
	 * Para obtener los otros atributos del nivel contas con los siguientes
	 * metodos:
	 * 
	 * creador->getAnchoEscenario()
	 * creador->getAltoEscenario()
	 * creador->getDuracion()
	 * creador->getRutaImagenFondo(): Ya se valida que haya elegido alguna.
	 * 
	 * Una vez hecho esto hay que llamar a:
	 * 
	 * informable->editarNivel(PARAMETRO, true)
	 * 
	 * Donde PARAMETRO es el nombre del archivo xml del nivel que se acaba de
	 * crear. El segundo parametro sirve para indicar que el nivel es nuevo, lo
	 * que luego hace que no se cargue un escenario ya existente y que los
	 * parametros propios de la entrada de los pajaros enemigos tomen valores
	 * por defecto.
	 */
}

void PanelNivel::cargarNiveles(std::string rutaMundo) {
	/*
	 * Informacion para Eze:
	 * 
	 * Aca hay que cargar en el mapa "idNiveles" que es atributo de este objeto
	 * los niveles del mundo para poder acceder a la ruta del archivo a partir
	 * del id del nivel.
	 * 
	 * Tambien debe cargarse en el atributo cantidadJugadores la cantidad de
	 * jugadores del mundo al cual pertenecen los niveles que se estan cargando.
	 * La idea de esto es poder acceder a ese atributo en el futuro sin tener
	 * que abrir el xml de nuevo.
	 */
	idNiveles[1] = "nivel_1.xml";
	idNiveles[2] = "nivel_2.xml";
	idNiveles[3] = "nivel_3.xml";
	cantidadJugadores = 2;
}

int PanelNivel::getCantidadJugadores() {
	return cantidadJugadores;
}
