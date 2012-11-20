#ifndef _PANEL_INICIAL_H_
#define _PANEL_INICIAL_H_

#include "PanelImagenFondo.h"
#include "InterfazSelectora.h"

#include <gtkmm/fixed.h>
#include <gtkmm/button.h>
#include <gtkmm/image.h>

//#include "../core/Client.h"

// Constantes de layout
#define ANCHO_BOTONES_INICIAL 100
#define ALTO_BOTONES_INICIAL 50
#define X_BOTON_UN_JUGADOR 400
#define Y_BOTON_UN_JUGADOR 100
#define X_BOTON_MULTIJUGADOR 400
#define Y_BOTON_MULTIJUGADOR 200
#define X_BOTON_SALIR 400
#define Y_BOTON_SALIR 300

class PanelInicial : public PanelImagenFondo {
	public:
	
		/**
		 * Constructor.
		 */
		PanelInicial(int ancho, int alto, string ruta,
												InterfazSelectora* interfaz);
		
		virtual ~PanelInicial();
		
	protected:
	
		/**
		 * El usuario ha indicado que quiere jugar en modo un jugador.
		 */
		void botonUnJugadorClickeado();
		
		/**
		 * El usuario ha indicado que quiere jugar en modo multijugador.
		 */
		void botonMultijugadorClickeado();
		
		/**
		 * El usuario ha indicado que quiere terminar la aplicacion.
		 */
		void botonSalirClickeado();
		
	private:
		
		/**
		 * Agrega los botones al panel
		 */
		void agregarBotones();
		
		InterfazSelectora* interfazSelectora;
	
		Gtk::Button* botonUnJugador;
		Gtk::Button* botonMultijugador;
		Gtk::Button* botonSalir;
};

#endif
