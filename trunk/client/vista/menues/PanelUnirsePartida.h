#ifndef _PANEL_UNIRSE_PARTIDA_H_
#define _PANEL_UNIRSE_PARTIDA_H_

#include <gtkmm/label.h>

#include <map>
#include <list>
#include <string>

#include "PanelImagenFondo.h"
#include "SeleccionadorMultiple.h"
#include "InterfazSelectora.h"

/**
 * Muestra al usuario una lista de las partidas existentes para jugar en modo
 * multijugador.
 */
class PanelUnirsePartida : public PanelImagenFondo {
public:
	/**
	 * Constructor.
	 */
	PanelUnirsePartida(int ancho, int alto, string ruta,
			InterfazSelectora& interfaz);

	/**
	 * Destructor.
	 */
	virtual ~PanelUnirsePartida();

	/**
	 * Carga las partidas existentes en una lista para poder mostrarlas.
	 */
	void cargarPartidas(std::string nombrePartidas);

	/**
	 * @return nombre de la partida elegida por el usuario
	 */
	string getPartidaElegida();

	Gtk::Button* botonUnirse;
	SeleccionadorMultiple* selectorPartidas;

private:
	/**
	 * El usuario indico que desea volver al menu multijugador.
	 */
	void botonVolverClickeado();

	InterfazSelectora& interfaz;
	Gtk::Button* botonVolver;

	std::map<string, string> partidas;
};

#endif
