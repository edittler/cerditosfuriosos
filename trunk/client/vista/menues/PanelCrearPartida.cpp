#include "PanelCrearPartida.h"

// Constantes del layout y tamanio del selector de mundos
#define X_SELECTOR_MUNDOS_PARTIDAS 75
#define Y_SELECTOR_MUNDOS_PARTIDAS 190
#define ANCHO_SELECTOR_MUNDOS_PARTIDAS 275
#define ALTO_SELECTOR_MUNDOS_PARTIDAS 250
// Constantes de layout y tamanio del boton crear
#define X_BOTON_CREACION_PARTIDA 425
#define Y_BOTON_CREACION_PARTIDA 350
#define ANCHO_BOTON_CREACION_PARTIDA 100
#define ALTO_BOTON_CREACION_PARTIDA 50
// Constantes de layout y tamanio del selector de nombre
#define X_NOMBRE_PARTIDA 75
#define Y_NOMBRE_PARTIDA 100
#define ANCHO_NOMBRE_PARTIDA 275
#define ALTO_NOMBRE_PARTIDA 30
// Constantes de layout del boton crear
#define X_BOTON_VOLVER_CREAR_PARTIDA 25
#define Y_BOTON_VOLVER_CREAR_PARTIDA 550
// Constantes de layout y tamanio de las etiquetas
#define X_ETIQUETA_NOMBRE_PARTIDA 75
#define Y_ETIQUETA_NOMBRE_PARTIDA 75
#define X_ETIQUETA_MUNDOS_PARTIDAS 75
#define Y_ETIQUETA_MUNDOS_PARTIDAS 160

PanelCrearPartida::PanelCrearPartida(int ancho, int alto, string ruta,
		InterfazSelectora& interfaz) :
		PanelImagenFondo(ancho, alto, ruta), interfaz(interfaz) {
	selectorMundos = NULL;

	// Inicializo la entrada del nombre
	nombre = new Gtk::Entry();
	nombre->set_size_request(ANCHO_NOMBRE_PARTIDA, ALTO_NOMBRE_PARTIDA);
	Gtk::Label* etiquetaNombre = manage(new Gtk::Label(
									"Seleccione un nombre para la partida"));
	put(*nombre, X_NOMBRE_PARTIDA, Y_NOMBRE_PARTIDA);
	put(*etiquetaNombre, X_ETIQUETA_NOMBRE_PARTIDA, Y_ETIQUETA_NOMBRE_PARTIDA);

	// Inicializo el boton crear
	botonCrear = new Gtk::Button("Crear");
	botonCrear->set_size_request(ANCHO_BOTON_CREACION_PARTIDA,
												ALTO_BOTON_CREACION_PARTIDA);
	Gtk::Label* etiquetaMundo = manage(new Gtk::Label("Seleccione un mundo"));
	put(*botonCrear, X_BOTON_CREACION_PARTIDA, Y_BOTON_CREACION_PARTIDA);
	put(*etiquetaMundo, X_ETIQUETA_MUNDOS_PARTIDAS, Y_ETIQUETA_MUNDOS_PARTIDAS);

	// Inicializo el botón volver al menu multijugador
	botonVolver = new Gtk::Button("Volver a menu multijugador");
	put(*botonVolver, X_BOTON_VOLVER_CREAR_PARTIDA,
												Y_BOTON_VOLVER_CREAR_PARTIDA);

	// Inicializo Seniales
	botonVolver->signal_clicked().connect(sigc::mem_fun(*this,
									&PanelCrearPartida::botonVolverClickeado));
}

PanelCrearPartida::~PanelCrearPartida() {
	if (selectorMundos != NULL)
		delete selectorMundos;
	delete nombre;
	delete botonCrear;
	delete botonVolver;
}

void PanelCrearPartida::cargarMundos(std::string nombreMundos) {
	// Limpio la entrada donde se almacena el nombre de la partida
	this->nombre->set_text("");
	// Limpio el mapa de mundo y cargo los que recibe por parametro.
	mundos.clear();
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
	if (selectorMundos != NULL)
		delete selectorMundos;
	selectorMundos = new SeleccionadorMultiple(ANCHO_SELECTOR_MUNDOS_PARTIDAS,
										ALTO_SELECTOR_MUNDOS_PARTIDAS, mundos);
	put(*selectorMundos, X_SELECTOR_MUNDOS_PARTIDAS,
												Y_SELECTOR_MUNDOS_PARTIDAS);
}

std::string PanelCrearPartida::getMundoElegido() {
	return selectorMundos->getOpcionSeleccionada();
}

std::string PanelCrearPartida::getNombreElegido() const {
	return nombre->get_text();
}

void PanelCrearPartida::botonVolverClickeado() {
	interfaz.modoMultijugador();
}
