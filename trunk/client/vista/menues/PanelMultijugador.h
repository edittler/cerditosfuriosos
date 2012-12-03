#ifndef _PANEL_MULTIJUGADOR_H_
#define _PANEL_MULTIJUGADOR_H_

#include "PanelImagenFondo.h"
#include "InterfazSelectora.h"

#include <gtkmm/fixed.h>
#include <gtkmm/button.h>
#include <gtkmm/image.h>

/**
 * Muestra al usuario las opciones de crear una partida multijugador, unirse a
 * una ya existente, o de ver los records.
 */
class PanelMultijugador : public PanelImagenFondo {
public:
	/**
	 * Constructor.
	 */
	PanelMultijugador(int ancho, int alto, string ruta,
			InterfazSelectora& interfaz);

	virtual ~PanelMultijugador();

	Gtk::Button* botonCrearPartida;
	Gtk::Button* botonUnirsePartida;
	Gtk::Button* botonRecords;
	Gtk::Button* botonVolver;

protected:

	/**
	 * El usuario ha indicado que quiere crear una partida.
	 */
	void botonCrearPartidaClickeado();

	/**
	 * El usuario ha indicado que quiere ver los records.
	 */
	void botonRecordsClickeado();

	/**
	 * El usuario ha indicado que quiere volver al menu inicial.
	 */
	void botonVolverClickeado();
	
private:
	/**
	 * Agrega los botones al panel
	 */
	void agregarBotones();

	InterfazSelectora& interfaz;
};

#endif
