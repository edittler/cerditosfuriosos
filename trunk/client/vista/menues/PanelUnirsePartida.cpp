#include "PanelUnirsePartida.h"

PanelUnirsePartida::PanelUnirsePartida(int ancho,
						int alto,
						string ruta,
						InterfazSelectora* interfaz) :
	PanelImagenFondo(ancho, alto, ruta)
{
	this->interfaz = interfaz;
	botonSeleccionar = new Gtk::Button("Seleccionar");
}

PanelUnirsePartida::~PanelUnirsePartida() {
	delete selectorPartidas;
	delete botonSeleccionar;
	delete botonVolver;
}

string PanelUnirsePartida::getPartidaElegida() {
	return selectorPartidas->getOpcionSeleccionada();
}
		
void PanelUnirsePartida::botonVolverClickeado() {
	interfaz->modoMultijugador();
}

void PanelUnirsePartida::cargarPartidas(std::list<string> nombrePartidas) {
	/* Aca se cargan las partidas en el contenedor atributo de este objeto
	 * llamado "partidas". */
	std::list<string>::iterator iterador = nombrePartidas.begin();
	while (iterador != nombrePartidas.end()) {
		partidas[*iterador] = *iterador;
		++iterador;	
	}
	agregarComponentes();
}

void PanelUnirsePartida::agregarComponentes() {
	selectorPartidas = new SeleccionadorMultiple(ANCHO_SELECTOR_PARTIDAS,
											ALTO_SELECTOR_PARTIDAS,	partidas);
	botonSeleccionar->set_size_request(ANCHO_BOTON_SELECCIONAR_PARTIDA,
												ALTO_BOTON_SELECCIONAR_PARTIDA);
	botonVolver = new Gtk::Button("Volver a menu multijugador");
	put(*selectorPartidas, X_SELECTOR_PARTIDAS, Y_SELECTOR_PARTIDAS);
	put(*botonSeleccionar, X_BOTON_SELECCIONAR_PARTIDA,
												Y_BOTON_SELECCIONAR_PARTIDA);
	put(*botonVolver, X_BOTON_VOLVER_PARTIDA, Y_BOTON_VOLVER_PARTIDA);
	Gtk::Label* etiqueta = manage(new Gtk::Label("Seleccione una partida"));
	put(*etiqueta, X_ETIQUETA_PARTIDAS, Y_ETIQUETA_PARTIDAS);
	// Seniales
	botonVolver->signal_clicked().connect(sigc::mem_fun(*this,
									&PanelUnirsePartida::botonVolverClickeado));
}
