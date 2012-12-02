#ifndef PANELESPERANDOJUGADORES_H_
#define PANELESPERANDOJUGADORES_H_

#include <gtkmm/button.h>

#include "PanelImagenFondo.h"
#include "InterfazSelectora.h"

class PanelEsperandoJugadores: public PanelImagenFondo {
public:
	PanelEsperandoJugadores(int ancho, int alto, string ruta,
			InterfazSelectora& interfaz);

	virtual ~PanelEsperandoJugadores();

	Gtk::Button* botonCancelar;

private:
	InterfazSelectora& interfaz;
};

#endif /* PANELESPERANDOJUGADORES_H_ */
