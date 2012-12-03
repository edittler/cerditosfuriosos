#include "PanelInicial.h"

// Constantes dimensiones de botones
#define ANCHO_BOTONES_INICIAL 120
#define ALTO_BOTONES_INICIAL 50
// Constantes de posicion de boton "Un jugador"
#define X_BOTON_UN_JUGADOR 90
#define Y_BOTON_UN_JUGADOR 450
// Constantes de posicion de boton "Multijugador"
#define X_BOTON_MULTIJUGADOR 390
#define Y_BOTON_MULTIJUGADOR 450
// Constantes de posicion de boton "Configuracion"
#define X_BOTON_CONFIGURACION 90
#define Y_BOTON_CONFIGURACION 525
// Constantes de posicion de boton "Salir"
#define X_BOTON_SALIR 390
#define Y_BOTON_SALIR 525

PanelInicial::PanelInicial(int ancho, int alto, string ruta,
		InterfazSelectora& interfaz) :
		PanelImagenFondo(ancho, alto, ruta), interfaz(interfaz) {
	agregarBotones();
}

PanelInicial::~PanelInicial() {
	delete botonUnJugador;
	delete botonMultijugador;
	delete botonSalir;
}

void PanelInicial::agregarBotones() {
	// Inicializo los botones
	botonUnJugador = new Gtk::Button("Un jugador");
	botonMultijugador = new Gtk::Button("Multijugador");
	botonConfiguracion = new Gtk::Button("Configuración");
	botonSalir = new Gtk::Button("Salir");
	// Les seteo sus dimensiones
	botonUnJugador->set_size_request(ANCHO_BOTONES_INICIAL,
														ALTO_BOTONES_INICIAL);
	botonMultijugador->set_size_request(ANCHO_BOTONES_INICIAL,
														ALTO_BOTONES_INICIAL);
	botonConfiguracion->set_size_request(ANCHO_BOTONES_INICIAL,
														ALTO_BOTONES_INICIAL);
	botonSalir->set_size_request(ANCHO_BOTONES_INICIAL, ALTO_BOTONES_INICIAL);
	// Los agrego al panel
	put(*botonUnJugador, X_BOTON_UN_JUGADOR, Y_BOTON_UN_JUGADOR);
	put(*botonMultijugador, X_BOTON_MULTIJUGADOR, Y_BOTON_MULTIJUGADOR);
	put(*botonConfiguracion, X_BOTON_CONFIGURACION, Y_BOTON_CONFIGURACION);
	put(*botonSalir, X_BOTON_SALIR, Y_BOTON_SALIR);
	// Seniales
	botonUnJugador->signal_clicked().connect(sigc::mem_fun(*this,
									&PanelInicial::botonUnJugadorClickeado));
	botonConfiguracion->signal_clicked().connect(sigc::mem_fun(*this,
								&PanelInicial::botonConfiguracionClickeado));
}

void PanelInicial::botonUnJugadorClickeado() {
	interfaz.modoUnJugador();
}

void PanelInicial::botonMultijugadorClickeado() {
	interfaz.modoMultijugador();
}

void PanelInicial::botonConfiguracionClickeado() {
	interfaz.modoConfiguracion("127.0.0.1", 23);
}

void PanelInicial::botonSalirClickeado() {
	get_window()->hide();
}
