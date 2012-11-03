#ifndef _VENTANA_DISENIADOR_H_
#define _VENTANA_DISENIADOR_H_
#include "PaletaEscenario.h"
#include "Lienzo.h"

#include <gtkmm.h>

/**
 * Ventana principal de la aplicacion diseniador.
 */
class VentanaDiseniador : public Gtk::Window {
	public:
	
		/**
		 * Constructor.
		 */
		VentanaDiseniador();
		
		/**
		 * Destructor.
		 */
		virtual ~VentanaDiseniador();
		
	protected:
	
		Gtk::HBox caja;
		PaletaEscenario paletaEscenario;
		Lienzo lienzo;
		
		std::list<Gtk::TargetEntry> listaObjetivos;
};

#endif
