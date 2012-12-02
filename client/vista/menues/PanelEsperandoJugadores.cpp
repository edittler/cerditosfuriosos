#include "PanelEsperandoJugadores.h"

// Constantes de layout y tamanio del boton guardar
#define X_BOTON_CANCELAR 450
#define Y_BOTON_CANCELAR 525
#define ANCHO_BOTON_CANCELAR 100
#define ALTO_BOTON_CANCELAR 50

PanelEsperandoJugadores::PanelEsperandoJugadores(int ancho, int alto,
		string ruta, InterfazSelectora& interfaz) :
		PanelImagenFondo(ancho, alto, ruta), interfaz(interfaz) {
	// Inicializo el boton de Cancelar
	botonCancelar = new Gtk::Button("Cancelar");
	botonCancelar->set_size_request(ANCHO_BOTON_CANCELAR, ALTO_BOTON_CANCELAR);
	put(*botonCancelar, X_BOTON_CANCELAR, Y_BOTON_CANCELAR);
}

PanelEsperandoJugadores::~PanelEsperandoJugadores() {
	delete botonCancelar;
}
