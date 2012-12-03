#include "PanelUnirsePartida.h"

// Constantes del layout y tamanio del selector
#define X_SELECTOR_PARTIDAS 75
#define Y_SELECTOR_PARTIDAS 200
#define ANCHO_SELECTOR_PARTIDAS 275
#define ALTO_SELECTOR_PARTIDAS 250
// Constantes de layout y tamanio del boton seleccionar
#define X_BOTON_SELECCIONAR_PARTIDA 425
#define Y_BOTON_SELECCIONAR_PARTIDA 300
#define ANCHO_BOTON_SELECCIONAR_PARTIDA 100
#define ALTO_BOTON_SELECCIONAR_PARTIDA 50
// Constantes de layout del boton volver
#define X_BOTON_VOLVER_PARTIDA 25
#define Y_BOTON_VOLVER_PARTIDA 550
// Constantes de layout y tamanio de las etiquetas
#define X_ETIQUETA_PARTIDAS 75
#define Y_ETIQUETA_PARTIDAS 150

PanelUnirsePartida::PanelUnirsePartida(int ancho, 	int alto, string ruta,
		InterfazSelectora& interfaz) :
	PanelImagenFondo(ancho, alto, ruta), interfaz(interfaz) {
	selectorPartidas = NULL;

	// Inicializo etiqueta de selector de partidas
	Gtk::Label* etiqueta = manage(new Gtk::Label("Seleccione una partida"));
	put(*etiqueta, X_ETIQUETA_PARTIDAS, Y_ETIQUETA_PARTIDAS);

	// Inicializo el boton unirse
	botonUnirse = new Gtk::Button("Unirse");
	botonUnirse->set_size_request(ANCHO_BOTON_SELECCIONAR_PARTIDA,
											ALTO_BOTON_SELECCIONAR_PARTIDA);
	put(*botonUnirse, X_BOTON_SELECCIONAR_PARTIDA,
												Y_BOTON_SELECCIONAR_PARTIDA);

	// Inicializo boton volver
	botonVolver = new Gtk::Button("Volver a menu multijugador");
	put(*botonVolver, X_BOTON_VOLVER_PARTIDA, Y_BOTON_VOLVER_PARTIDA);

	// Inicializo Señales
	botonVolver->signal_clicked().connect(sigc::mem_fun(*this,
									&PanelUnirsePartida::botonVolverClickeado));
}

PanelUnirsePartida::~PanelUnirsePartida() {
	if (selectorPartidas != NULL)
		delete selectorPartidas;
	delete botonUnirse;
	delete botonVolver;
}

string PanelUnirsePartida::getPartidaElegida() {
	return selectorPartidas->getOpcionSeleccionada();
}
		
void PanelUnirsePartida::botonVolverClickeado() {
	interfaz.modoMultijugador();
}

void PanelUnirsePartida::cargarPartidas(std::string nombrePartidas) {
	partidas.clear();
	unsigned int contador = 0;
	std::string nombre;
	while (contador < nombrePartidas.length()) {
		std::string nombre;
		std::string clave;
		bool seEncontroDelimitador = false;
		while (nombrePartidas[contador] != '%') {
			nombre += nombrePartidas[contador];
			if (seEncontroDelimitador)
				clave += nombrePartidas[contador];
			if (nombrePartidas[contador] == ':')
				seEncontroDelimitador = true;
			++contador;
		}
		++contador;
		partidas[clave] = nombre;
	}
	if (selectorPartidas != NULL)
		delete selectorPartidas;
	selectorPartidas = new SeleccionadorMultiple(ANCHO_SELECTOR_PARTIDAS,
											ALTO_SELECTOR_PARTIDAS, partidas);

	put(*selectorPartidas, X_SELECTOR_PARTIDAS, Y_SELECTOR_PARTIDAS);
}
