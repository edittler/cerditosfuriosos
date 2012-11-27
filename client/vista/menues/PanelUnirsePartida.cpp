#include "PanelUnirsePartida.h"

PanelUnirsePartida::PanelUnirsePartida(int ancho,
						int alto,
						string ruta,
						InterfazSelectora* interfaz) :
	PanelImagenFondo(ancho, alto, ruta)
{
	this->interfaz = interfaz;
	selectorPartidas = NULL;
	botonSeleccionar = new Gtk::Button("Seleccionar");
	botonVolver = new Gtk::Button("Volver a menu multijugador");
}

PanelUnirsePartida::~PanelUnirsePartida() {
	if (selectorPartidas != NULL)
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

void PanelUnirsePartida::cargarPartidas(std::string nombrePartidas) {
	unsigned int contador = 0;
	std::string nombre;
	while (contador < nombrePartidas.length()) {
		std::string nombre("");
		while (nombrePartidas[contador] != '%') {
			nombre += nombrePartidas[contador];
			++contador;
		}
		++contador;
		partidas[nombre] = nombre;
	}
	agregarComponentes();
}

void PanelUnirsePartida::agregarComponentes() {
	selectorPartidas = new SeleccionadorMultiple(ANCHO_SELECTOR_PARTIDAS,
											ALTO_SELECTOR_PARTIDAS,	partidas);
	botonSeleccionar->set_size_request(ANCHO_BOTON_SELECCIONAR_PARTIDA,
												ALTO_BOTON_SELECCIONAR_PARTIDA);
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
