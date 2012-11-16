#ifndef _PANEL_ESCENARIO_H_
#define _PANEL_ESCENARIO_H_

#include <gtkmm/paned.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>

#include "PaletaEscenario.h"
#include "EliminadorPosicionables.h"
#include "Lienzo.h"
#include "EntradaPajaros.h"
#include "InformableSeleccion.h"

/**
 * Muestra el panel que permite editar un escenario.
 */
class PanelEscenario : public Gtk::Paned {
	public:
	
		/**
		 * Constructor.
		 */
		PanelEscenario(std::string rutaNivel, InformableSeleccion* informable, int cantidadJugadores);
		
		/**
		 * Destructor.
		 */
		~PanelEscenario();
	
	protected:
	
		/**
		 * Metodo invocado cuando se clickea al boton que guarda el nivel.
		 * Previamente a guardar exije al usario que deje al escenario en un
		 * estado valido si este no es asi.
		 */
		void botonGuardarClickeado();
	
	private:
	
		PaletaEscenario* paletaEscenario;
		EliminadorPosicionables* eliminador;
		Lienzo* lienzo;
		EntradaPajaros* entrada;
		Gtk::Button* botonGuardar;
		
		InformableSeleccion* informable;
		std::string rutaNivel;
		int cantidadJugadores;
};

#endif
