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

void PanelInicial::agregarBotones() {
	botonUnJugador = new Gtk::Button("Un jugador");
	botonMultijugador = new Gtk::Button("Multijugador");
	botonConfiguracion = new Gtk::Button("Configuración");
	botonSalir = new Gtk::Button("Salir");
	botonUnJugador->set_size_request(ANCHO_BOTONES_INICIAL,
														ALTO_BOTONES_INICIAL);
	botonMultijugador->set_size_request(ANCHO_BOTONES_INICIAL,
														ALTO_BOTONES_INICIAL);
	botonConfiguracion->set_size_request(ANCHO_BOTONES_INICIAL,
														ALTO_BOTONES_INICIAL);
	botonSalir->set_size_request(ANCHO_BOTONES_INICIAL, ALTO_BOTONES_INICIAL);
	put(*botonUnJugador, X_BOTON_UN_JUGADOR, Y_BOTON_UN_JUGADOR);
	put(*botonMultijugador, X_BOTON_MULTIJUGADOR, Y_BOTON_MULTIJUGADOR);
	put(*botonConfiguracion, X_BOTON_CONFIGURACION, Y_BOTON_CONFIGURACION);
	put(*botonSalir, X_BOTON_SALIR, Y_BOTON_SALIR);
	// Seniales
	botonUnJugador->signal_clicked().connect(sigc::mem_fun(*this,
									&PanelInicial::botonUnJugadorClickeado));
//	botonMultijugador->signal_clicked().connect(sigc::mem_fun(*this,
//								&PanelInicial::botonMultijugadorClickeado));
	botonConfiguracion->signal_clicked().connect(sigc::mem_fun(*this,
								&PanelInicial::botonConfiguracionClickeado));
//	botonSalir->signal_clicked().connect(sigc::mem_fun(*this,
//										&PanelInicial::botonSalirClickeado));
}

void PanelInicial::botonUnJugadorClickeado() {
	interfazSelectora->modoUnJugador();
}

void PanelInicial::botonMultijugadorClickeado() {
	interfazSelectora->modoMultijugador();
}

void PanelInicial::botonConfiguracionClickeado() {
	interfazSelectora->modoConfiguracion("127.0.0.1", 23);
}

void PanelInicial::botonSalirClickeado() {
	get_window()->hide();
}
