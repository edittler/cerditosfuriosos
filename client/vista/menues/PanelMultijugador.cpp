#include "PanelMultijugador.h"

// Constantes de dimensiones de botones
#define ANCHO_BOTONES_MULTIJUGADOR 150
#define ALTO_BOTONES_MULTIJUGADOR 50
// Constantes de posicion de boton "Crear partida"
#define X_BOTON_CREAR_PARTIDA 25
#define Y_BOTON_CREAR_PARTIDA 450
// Constantes de posicion de boton "Unirse a partida"
#define X_BOTON_UNIRSE_PARTIDA 225
#define Y_BOTON_UNIRSE_PARTIDA 450
// Constantes de posicion de boton "Ver records"
#define X_BOTON_RECORDS 425
#define Y_BOTON_RECORDS 450
// Constantes de posicion de boton "Volver a menu principal"
#define X_BOTON_VOLVER 25
#define Y_BOTON_VOLVER 550

PanelMultijugador::PanelMultijugador(int ancho, int alto, string ruta,
		InterfazSelectora& interfaz) :
		PanelImagenFondo(ancho, alto, ruta), interfaz(interfaz) {
	agregarBotones();
}

PanelMultijugador::~PanelMultijugador() {
	delete botonCrearPartida;
	delete botonUnirsePartida;
	delete botonRecords;
	delete botonVolver;
}

void PanelMultijugador::botonCrearPartidaClickeado() { }

void PanelMultijugador::botonRecordsClickeado() {
	interfaz.verRecords();
}

void PanelMultijugador::botonVolverClickeado() {
	interfaz.volverAMenuPrincipal();
}

void PanelMultijugador::agregarBotones() {
	// Creo los botones
	botonCrearPartida = new Gtk::Button("Crear partida");
	botonUnirsePartida = new Gtk::Button("Unirse a partida");
	botonRecords = new Gtk::Button("Ver records");
	botonVolver = new Gtk::Button("Volver al menu principal");
	// Les seteo sus dimenciones
	botonCrearPartida->set_size_request(ANCHO_BOTONES_MULTIJUGADOR,
													ALTO_BOTONES_MULTIJUGADOR);
	botonUnirsePartida->set_size_request(ANCHO_BOTONES_MULTIJUGADOR,
													ALTO_BOTONES_MULTIJUGADOR);
	botonRecords->set_size_request(ANCHO_BOTONES_MULTIJUGADOR,
													ALTO_BOTONES_MULTIJUGADOR);
	// Los posiciono en el panel
	put(*botonCrearPartida, X_BOTON_CREAR_PARTIDA, Y_BOTON_CREAR_PARTIDA);
	put(*botonUnirsePartida, X_BOTON_UNIRSE_PARTIDA, Y_BOTON_UNIRSE_PARTIDA);
	put(*botonRecords, X_BOTON_RECORDS, Y_BOTON_RECORDS);
	put(*botonVolver, X_BOTON_VOLVER, Y_BOTON_VOLVER);
	// Inicializo las seniales
	botonRecords->signal_clicked().connect(sigc::mem_fun(*this,
									&PanelMultijugador::botonRecordsClickeado));
}
