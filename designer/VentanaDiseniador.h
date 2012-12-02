#ifndef _VENTANA_DISENIADOR_H_
#define _VENTANA_DISENIADOR_H_

#include <gtkmm/window.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/stock.h>
#include <gtkmm/filefilter.h>

#include "PanelNivel.h"
#include "PanelMundo.h"
#include "PanelEscenario.h"

/**
 * Ventana principal de la aplicacion diseniador.
 */
class VentanaDiseniador : public Gtk::Window, public InformableSeleccion {
	public:
	
		/**
		 * Constructor.
		 */
		VentanaDiseniador();
		
		/**
		 * Destructor.
		 */
		virtual ~VentanaDiseniador();
		
		virtual void volverAPanelMundos();
		
		virtual void editarMundo(std::string rutaMundo);
		
		virtual void nombreSeleccionadoVacio();
		
		virtual void nombreSeleccionadoYaExistente();
		
		virtual void editarNivel(std::string rutaNivel, bool nivelNuevo);
		
		virtual void imagenNoSeleccionada();
		
		virtual std::string seleccionarImagen();
		
		virtual void mostrarDialogo(std::string mensaje);
		
		/**
		 * Si estamos en el panel de creacion de escenarios y el escenario es
		 * valido simplemente se cierra la ventana, si no le solicita al usuario
		 * que lo deje en un estado valido para continuar.
		 */
		bool cerrarVentana(GdkEventAny* event);
		
	private:
	
		PanelMundo* panelMundo;
		PanelNivel* panelNivel;
		PanelEscenario* panelEscenario;
};

#endif
