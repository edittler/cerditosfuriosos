#ifndef _VENTANA_DISENIADOR_H_
#define _VENTANA_DISENIADOR_H_

#include <gtkmm/window.h>

#include "PanelInicial.h"
#include "PanelUnJugador.h"
#include "PanelMultijugador.h"
#include "PanelUnirsePartida.h"
#include "PanelRecords.h"
#include "InterfazSelectora.h"

/**
 * Ventana principal de la aplicacion.
 */
class VentanaPrincipal : public Gtk::Window, public InterfazSelectora {
	public:
	
		/**
		 * Constructor.
		 */
		VentanaPrincipal();
		
		/**
		 * Destructor.
		 */
		virtual ~VentanaPrincipal();
		
		virtual void modoUnJugador();
		virtual void volverAMenuPrincipal();
		virtual void modoMultijugador();
		virtual void unirseAPartida();
		virtual void verRecords();

		
	private:
	
		PanelInicial* panelInicial;
		PanelUnJugador* panelUnJugador;
		PanelMultijugador* panelMultijugador;
		PanelUnirsePartida* panelUnirsePartida;
		PanelRecords* panelRecords;
};

#endif
