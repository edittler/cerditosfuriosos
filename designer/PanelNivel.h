#ifndef _PANEL_NIVEL_H_
#define _PANEL_NIVEL_H_

#include <gtkmm/frame.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>

#include "SelectorNiveles.h"
#include "CreadorNivel.h"
#include "InformableSeleccion.h"

class PanelNivel : public Gtk::Paned {
	public:
	
		/**
		 * Constructor.
		 */
		PanelNivel(std::string rutaMundo);
		
		/**
		 * Destructor.
		 */
		virtual ~PanelNivel();
		
		/**
		 * @param informable el objeto al que se le informara cuando el usuario
		 * ingrese informacion relevante
		 */
		void setInformable(InformableSeleccion* informable);
	
	protected:
	
		/**
		 * Metodo llamado cuando se clickea el boton de creacion de mundo.
		 */
		void botonCrearClickeado();
	
	private:
		
		InformableSeleccion* informable;
		SelectorNiveles* selector;
		CreadorNivel* creador;
		Gtk::Button* botonEditar;
		Gtk::Button* botonCrear;
		
		std::map<std::string, int> idNiveles;
		
		/**
		 * Carga en un contenedor mapa los id de los niveles de un mundo, para
		 * ser accedidos a partir de la ruta de los archivos de los mismos.
		 * @param rutaMundo ruta del archivo que contiene al mundo al cual
		 * pertenecen los niveles
		 */
		void cargarIdNiveles(std::string rutaMundo);
};

#endif
