#ifndef _PANEL_INICIAL_H_
#define _PANEL_INICIAL_H_

#include "PanelImagenFondo.h"
#include "InterfazSelectora.h"

#include <gtkmm/fixed.h>
#include <gtkmm/button.h>
#include <gtkmm/image.h>

class PanelInicial : public PanelImagenFondo {
public:

	/**
	 * Constructor.
	 */
	PanelInicial(int ancho, int alto, string ruta, InterfazSelectora& interfaz);

	virtual ~PanelInicial();

	Gtk::Button* botonMultijugador;
	Gtk::Button* botonConfiguracion;
	Gtk::Button* botonSalir;

private:
	/**
	 * Agrega los botones al panel
	 */
	void agregarBotones();

	/**
	 * El usuario ha indicado que quiere jugar en modo un jugador.
	 */
	void botonUnJugadorClickeado();

	/**
	 * El usuario ha indicado que quiere jugar en modo multijugador.
	 */
	void botonMultijugadorClickeado();

	/**
	 * El usuario ha indicado que quiere ajustar la configuracion.
	 */
	void botonConfiguracionClickeado();

	/**
	 * El usuario ha indicado que quiere terminar la aplicacion.
	 */
	void botonSalirClickeado();

	InterfazSelectora& interfaz;

	Gtk::Button* botonUnJugador;
};

#endif
