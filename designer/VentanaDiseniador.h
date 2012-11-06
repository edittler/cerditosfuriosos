#ifndef _VENTANA_DISENIADOR_H_
#define _VENTANA_DISENIADOR_H_
#include "PaletaEscenario.h"
#include "EliminadorPosicionables.h"
#include "Lienzo.h"
#include <gtkmm/window.h>
#include <gtkmm/targetentry.h>
#include <gtkmm/box.h>

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
	
		/* Objetos con funcionalidad */
		PaletaEscenario* paletaEscenario;
		EliminadorPosicionables* eliminador;
		Lienzo* lienzo;
		/* */
		Gtk::VBox cajaPaletaBorrar;
		Gtk::HBox caja;
};

#endif
