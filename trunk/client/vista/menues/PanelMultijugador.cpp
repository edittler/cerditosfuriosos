#include "PanelMultijugador.h"

PanelMultijugador::PanelMultijugador(int ancho, int alto, string ruta,
												InterfazSelectora* interfaz) :
	PanelImagenFondo(ancho, alto, ruta)
{
	this->interfaz = interfaz;
	agregarBotones();
}

PanelMultijugador::~PanelMultijugador() {
	delete botonCrearPartida;
	delete botonUnirsePartida;
	delete botonRecords;
	delete botonVolver;
}

void PanelMultijugador::botonCrearPartidaClickeado() {
	
}

void PanelMultijugador::botonUnirsePartidaClickeado() {
	interfaz->unirseAPartida();
}

void PanelMultijugador::botonRecordsClickeado() {
	interfaz->verRecords();
}

void PanelMultijugador::botonVolverClickeado() {
	interfaz->volverAMenuPrincipal();
}

void PanelMultijugador::agregarBotones() {
	botonCrearPartida = new Gtk::Button("Crear partida");
	botonUnirsePartida = new Gtk::Button("Unirse a partida");
	botonRecords = new Gtk::Button("Ver records");
	botonVolver = new Gtk::Button("Volver al menu principal");
	botonCrearPartida->set_size_request(ANCHO_BOTONES_MULTIJUGADOR,
													ALTO_BOTONES_MULTIJUGADOR);
	botonUnirsePartida->set_size_request(ANCHO_BOTONES_MULTIJUGADOR,
													ALTO_BOTONES_MULTIJUGADOR);
	botonRecords->set_size_request(ANCHO_BOTONES_MULTIJUGADOR,
													ALTO_BOTONES_MULTIJUGADOR);
	put(*botonCrearPartida, X_BOTON_CREAR_PARTIDA, Y_BOTON_CREAR_PARTIDA);
	put(*botonUnirsePartida, X_BOTON_UNIRSE_PARTIDA, Y_BOTON_UNIRSE_PARTIDA);
	put(*botonRecords, X_BOTON_RECORDS, Y_BOTON_RECORDS);
	put(*botonVolver, X_BOTON_VOLVER, Y_BOTON_VOLVER);
	// Seniales
//	botonCrearPartida->signal_clicked().connect(sigc::mem_fun(*this,
//							&PanelMultijugador::botonCrearPartidaClickeado));
	botonUnirsePartida->signal_clicked().connect(sigc::mem_fun(*this,
							&PanelMultijugador::botonUnirsePartidaClickeado));
	botonRecords->signal_clicked().connect(sigc::mem_fun(*this,
									&PanelMultijugador::botonRecordsClickeado));
//	botonVolver->signal_clicked().connect(sigc::mem_fun(*this,
//									&PanelMultijugador::botonVolverClickeado));
}
