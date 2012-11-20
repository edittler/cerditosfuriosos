#include "PanelInicial.h"

PanelInicial::PanelInicial(int ancho, int alto, string ruta,
												InterfazSelectora* interfaz) :
	PanelImagenFondo(ancho, alto, ruta)
{
	this->interfazSelectora = interfaz;
	agregarBotones();
}

PanelInicial::~PanelInicial() {
	delete botonUnJugador;
	delete botonMultijugador;
	delete botonSalir;
}

void PanelInicial::botonUnJugadorClickeado() {
	interfazSelectora->modoUnJugador();
}

void PanelInicial::botonMultijugadorClickeado() {
	interfazSelectora->modoMultijugador();
}

void PanelInicial::botonSalirClickeado() {
	get_window()->hide();
}

void PanelInicial::agregarBotones() {
	botonUnJugador = new Gtk::Button("Un jugador");
	botonMultijugador = new Gtk::Button("Multijugador");
	botonSalir = new Gtk::Button("Salir");
	botonUnJugador->set_size_request(ANCHO_BOTONES_INICIAL,
														ALTO_BOTONES_INICIAL);
	botonMultijugador->set_size_request(ANCHO_BOTONES_INICIAL,
														ALTO_BOTONES_INICIAL);
	botonSalir->set_size_request(ANCHO_BOTONES_INICIAL, ALTO_BOTONES_INICIAL);
	put(*botonUnJugador, X_BOTON_UN_JUGADOR, Y_BOTON_UN_JUGADOR);
	put(*botonMultijugador, X_BOTON_MULTIJUGADOR, Y_BOTON_MULTIJUGADOR);
	put(*botonSalir, X_BOTON_SALIR, Y_BOTON_SALIR);
	// Seniales
	botonUnJugador->signal_clicked().connect(sigc::mem_fun(*this,
									&PanelInicial::botonUnJugadorClickeado));
	botonMultijugador->signal_clicked().connect(sigc::mem_fun(*this,
									&PanelInicial::botonMultijugadorClickeado));
	botonSalir->signal_clicked().connect(sigc::mem_fun(*this,
										&PanelInicial::botonSalirClickeado));
}
