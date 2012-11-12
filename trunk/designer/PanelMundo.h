#ifndef _PANEL_MUNDOS_H_
#define _PANEL_MUNDOS_H_
#include "SelectorMundos.h"
#include "CreadorMundo.h"
#include "InformableSeleccion.h"

#include <gtkmm/button.h>
#include <gtkmm/separator.h>
#include <gtkmm/frame.h>
#include <gtkmm/buttonbox.h>

/**
 * Muestra al usuario la opcion de optar por uno de los mundos ya creados para
 * editarlo o de crear uno nuevo.
 */
class PanelMundo : public Gtk::Paned {
	public:
	
		/**
		 * Creador.
		 */
		PanelMundo();
		
		/**
		 * Destructor.
		 */
		virtual ~PanelMundo();
		
		/**
		 * @param informable el objeto al que se le informara cuando el usuario
		 * ingrese informacion relevante
		 */
		void setInformable(InformableSeleccion* informable);
	
	protected:
		
		/**
		 * Metodo llamado cuando se clickea el boton de edicion de mundo.
		 */
		void botonEditarClickeado();
		
		/**
		 * Metodo llamado cuando se clickea el boton de creacion de mundo.
		 */
		void botonCrearClickeado();
		
	private:
	
		InformableSeleccion* informable;
		SelectorMundos* selector;
		CreadorMundo* creador;
		Gtk::Button* botonEditar;
		Gtk::Button* botonCrear;
		
		std::map<std::string, std::string> nombreMundos;
		
		/**
		 * Crea un contenedor mapa que permite acceder a los nombres de los
		 * mundos a partir de la ruta de su archivo.
		 */
		void cargarNombreMundos();
};

#endif
