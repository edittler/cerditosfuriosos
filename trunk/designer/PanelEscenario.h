#ifndef _PANEL_ESCENARIO_H_
#define _PANEL_ESCENARIO_H_

#include <gtkmm/paned.h>

#include "PaletaEscenario.h"
#include "EliminadorPosicionables.h"
#include "Lienzo.h"

/**
 * Muestra el panel que permite editar un escenario.
 */
class PanelEscenario : public Gtk::Paned {
	public:
	
		/**
		 * Constructor.
		 */
		PanelEscenario();
		
		/**
		 * Destructor.
		 */
		~PanelEscenario();
		
	private:
	
		PaletaEscenario* paletaEscenario;
		EliminadorPosicionables* eliminador;
		Lienzo* lienzo;
};

#endif
