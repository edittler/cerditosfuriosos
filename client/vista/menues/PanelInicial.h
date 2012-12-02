#ifndef _PANEL_INICIAL_H_
#define _PANEL_INICIAL_H_

#include "PanelImagenFondo.h"
#include "InterfazSelectora.h"

#include <gtkmm/fixed.h>
#include <gtkmm/button.h>
#include <gtkmm/image.h>

//#include "../core/Client.h"

// Constantes de layout
#define ANCHO_BOTONES_INICIAL 120
#define ALTO_BOTONES_INICIAL 50
#define X_BOTON_UN_JUGADOR 400
#define Y_BOTON_UN_JUGADOR 150
#define X_BOTON_MULTIJUGADOR 400
#define Y_BOTON_MULTIJUGADOR 250
#define X_BOTON_CONFIGURACION 400
#define Y_BOTON_CONFIGURACION 350
#define X_BOTON_SALIR 400
#define Y_BOTON_SALIR 450

class PanelInicial : public PanelImagenFondo {
public:

	/**
	 * Constructor.
	 */
	PanelInicial(int ancho, int alto, string ruta, InterfazSelectora* interfaz);

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

	InterfazSelectora* interfazSelectora;

	Gtk::Button* botonUnJugador;
};

#endif
