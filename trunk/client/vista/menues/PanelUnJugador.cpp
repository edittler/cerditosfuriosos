#include "PanelUnJugador.h"

PanelUnJugador::PanelUnJugador(int ancho,
								int alto,
								string ruta,
								InterfazSelectora* interfaz):
	PanelImagenFondo(ancho, alto, ruta)
{
	interfazSelectora = interfaz;
	cargarMundos();
	selectorMundos = new SeleccionadorMultiple(ANCHO_SELECTORES,
												ALTO_SELECTORES,
												mundos);
	conectarBotonesMundo();
	cargarNiveles(selectorMundos->getOpcionSeleccionada());
	selectorNiveles = new SeleccionadorMultiple(ANCHO_SELECTORES,
												ALTO_SELECTORES,
												niveles);
	agregarComponentes();
	// Seniales
//	botonSeleccionar->signal_clicked().connect(sigc::mem_fun(*this,
//								&PanelUnJugador::botonSeleccionarClickeado));
	botonVolver->signal_clicked().connect(sigc::mem_fun(*this,
										&PanelUnJugador::botonVolverClickeado));
}

PanelUnJugador::~PanelUnJugador() {
	delete selectorMundos;
	delete selectorNiveles;
	delete botonSeleccionar;
	delete botonVolver;
}

void PanelUnJugador::cargarMundos() {
	/*
	 * Aca deben cargarse en el mapa "mundos" las rutas de los archivos de los
	 * mundos, para poder accederlas a partir del nombre de los mismos.
	 * 
	 * Por ejemplo:
	 */
	mundos["Mundo 1"] = "mundo_1.xml";
	mundos["Mundo 2"] = "mundo_2.xml";
	mundos["Mundo 3"] = "mundo_3.xml";
	mundos["Mundo 4"] = "mundo_4.xml";
}

void PanelUnJugador::cargarNiveles(string ruta) {
	// Se vacia el mapa de niveles para introducir los de otro mundo.
	vaciarMapaNiveles();
	/*
	 * Aca deben cargarse en el mapa "niveles" las rutas de los archivos de los
	 * niveles pertenecientes al nivel cuya ruta es pasada al metodo, para poder
	 * accederlas a partir del id de los mismos.
	 */
	if (ruta.compare("mundo_1.xml") == 0) {
		niveles[1] = "../common/MiMundo-level1.xml";
		niveles[2] = "../common/MiMundo-level1.xml";
		
	}
	if (ruta.compare("mundo_2.xml") == 0) {
		niveles[1] = "../common/MiMundo-level1.xml";
		niveles[2] = "../common/MiMundo-level1.xml";
		niveles[3] = "../common/MiMundo-level1.xml";
		niveles[4] = "../common/MiMundo-level1.xml";
	}
	if (ruta.compare("mundo_3.xml") == 0) {
		niveles[1] = "../common/MiMundo-level1.xml";
		niveles[2] = "../common/MiMundo-level1.xml";
		niveles[3] = "../common/MiMundo-level1.xml";
	}
	if (ruta.compare("mundo_4.xml") == 0) {
		niveles[1] = "../common/MiMundo-level1.xml";
		niveles[2] = "../common/MiMundo-level1.xml";
		niveles[3] = "../common/MiMundo-level1.xml";
		niveles[4] = "../common/MiMundo-level1.xml";
		niveles[5] = "../common/MiMundo-level1.xml";
	}
}

void PanelUnJugador::vaciarMapaNiveles() {
	while (!(niveles.empty()))
		niveles.erase(niveles.begin());
}

void PanelUnJugador::mundoSeleccionadoCambiado() {
	cargarNiveles(selectorMundos->getOpcionSeleccionada());
	selectorNiveles->actualizarBotones(niveles);
	selectorNiveles->show_all();
}

void PanelUnJugador::conectarBotonesMundo() {
	int contador = 0;
	while (contador < selectorMundos->cantidadBotones) {
		selectorMundos->botones[contador]->signal_toggled().connect(
			sigc::mem_fun(*this, &PanelUnJugador::mundoSeleccionadoCambiado));
		++contador;
	}
}

void PanelUnJugador::agregarComponentes() {
	Gtk::Label* etiquetaMundos = manage(new Gtk::Label("Seleccione un mundo"));
	Gtk::Label* etiquetaNiveles = manage(new Gtk::Label("Seleccione un nivel"));
	put(*etiquetaMundos, X_ETIQUETA_MUNDOS, Y_ETIQUETAS);
	put(*etiquetaNiveles, X_ETIQUETA_NIVELES, Y_ETIQUETAS);
	put(*selectorMundos, X_SELECTOR_MUNDOS, Y_SELECTORES);
	put(*selectorNiveles, X_SELECTOR_NIVELES, Y_SELECTORES);
	botonSeleccionar = new Gtk::Button("Seleccionar");
	botonSeleccionar->set_size_request(ANCHO_BOTON_SELECCIONAR, ALTO_BOTON_SELECCIONAR);
	put(*botonSeleccionar, X_BOTON_SELECCIONAR, Y_BOTON_SELECCIONAR);
	botonVolver = new Gtk::Button("Volver al menu principal");
	put(*botonVolver, X_BOTON_VOLVER, Y_BOTON_VOLVER);
}

void PanelUnJugador::botonVolverClickeado() {
	interfazSelectora->volverAMenuPrincipal();
}


void PanelUnJugador::botonSeleccionarClickeado() {

}

std::string PanelUnJugador::getRutaNivelSeleccionado() const {
	return selectorNiveles->getOpcionSeleccionada();
}
