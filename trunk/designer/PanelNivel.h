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
		 * @param rutaMundo ruta del archivo del mundo a quien le queremos
		 * agregar niveles o cuyos niveles queremos editar
		 * @param informable se le informara cuando el usuario seleccione
		 * ciertas informaciones de relevancia
		 */
		PanelNivel(std::string rutaMundo, InformableSeleccion* informable);
		
		/**
		 * Destructor.
		 */
		virtual ~PanelNivel();
		
	protected:
	
		/**
		 * Metodo llamado cuando se clickea el boton de creacion de mundo.
		 */
		void botonCrearClickeado();
		
		/**
		 * Metodo llamado cuando se clickea el boton de edicion de mundo.
		 */
		void botonEditarClickeado();
	
	private:
		
		InformableSeleccion* informable;
		SelectorNiveles* selector;
		CreadorNivel* creador;
		Gtk::Button* botonEditar;
		Gtk::Button* botonCrear;
		
		std::map<int, std::string> idNiveles;
		std::string rutaMundo;
		
		/**
		 * Carga en un contenedor mapa las rutas de los niveles, para ser
		 * accedidas a partir de la id de los mismos.
		 * @param rutaMundo ruta del archivo que contiene al mundo al cual
		 * pertenecen los niveles
		 */
		void cargarNiveles(std::string rutaMundo);
};

#endif
