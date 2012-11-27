#include "PanelCrearPartida.h"

PanelCrearPartida::PanelCrearPartida(int ancho, int alto, string ruta,
		InterfazSelectora* interfaz) : PanelImagenFondo(ancho, alto, ruta) {
	this->interfaz = interfaz;
	selectorMundos = new SeleccionadorMultiple(ANCHO_SELECTOR_MUNDOS_PARTIDAS,
										ALTO_SELECTOR_MUNDOS_PARTIDAS, mundos);
	nombre = new Gtk::Entry();
	botonCrear = new Gtk::Button("Crear");
	botonVolver = new Gtk::Button("Volver a menu multijugador");
}

PanelCrearPartida::~PanelCrearPartida() {
	delete selectorMundos;
	delete botonCrear;
	delete botonVolver;
	delete nombre;
}
		
void PanelCrearPartida::botonVolverClickeado() {
	interfaz->modoMultijugador();
}

void PanelCrearPartida::cargarMundos(std::string nombreMundos) {
	 unsigned int contador = 0;
	 std::string nombre;
	 while (contador < nombreMundos.length()) {
		 std::string nombre("");
		 while (nombreMundos[contador] != '%') {
			 nombre += nombreMundos[contador];
			 ++contador;
		 }
		 ++contador;
		 mundos[nombre] = nombre;
	 }
	 inicializarComponentes();
}

std::string PanelCrearPartida::getMundoElegido() {
	return selectorMundos->getOpcionSeleccionada();
}

std::string PanelCrearPartida::getNombreElegido() const {
	return nombre->get_text();
}

void PanelCrearPartida::inicializarComponentes() {
	botonCrear->set_size_request(ANCHO_BOTON_CREACION_PARTIDA,
												ALTO_BOTON_CREACION_PARTIDA);
	nombre->set_size_request(ANCHO_NOMBRE_PARTIDA, ALTO_NOMBRE_PARTIDA);
	put(*selectorMundos, X_SELECTOR_MUNDOS_PARTIDAS,
													Y_SELECTOR_MUNDOS_PARTIDAS);
	put(*botonCrear, X_BOTON_CREACION_PARTIDA, Y_BOTON_CREACION_PARTIDA);
	put(*botonVolver, X_BOTON_VOLVER_CREAR_PARTIDA,
												Y_BOTON_VOLVER_CREAR_PARTIDA);
	put(*nombre, X_NOMBRE_PARTIDA, Y_NOMBRE_PARTIDA);
	Gtk::Label* etiquetaMundo = manage(new Gtk::Label("Seleccione un mundo"));
	put(*etiquetaMundo, X_ETIQUETA_MUNDOS_PARTIDAS, Y_ETIQUETA_MUNDOS_PARTIDAS);
	Gtk::Label* etiquetaNombre = manage(new Gtk::Label(
									"Seleccione un nombre para la partida: "));
	put(*etiquetaNombre, X_ETIQUETA_NOMBRE_PARTIDA, Y_ETIQUETA_NOMBRE_PARTIDA);
	// Seniales
	botonVolver->signal_clicked().connect(sigc::mem_fun(*this,
									&PanelCrearPartida::botonVolverClickeado));
}
