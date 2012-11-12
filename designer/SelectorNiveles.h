#ifndef _SELECTOR_NIVELES_H_
#define _SELECTOR_NIVELES_H_

#include <gtkmm/scrolledwindow.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/box.h>

#include <map>
#include <string>

/**
 * Proporciona una ventana desplazable en la que hay un boton de radio por cada
 * nivel ya creado de un mundo determinado.
 */
class SelectorNiveles : public Gtk::ScrolledWindow {
	public:
	
		/**
		 * Constructor.
		 * @param idNiveles contenedor mapa dentro del cual a partir de la ruta
		 * del archivo de un nivel se accede a su indice
		 */
		SelectorNiveles(std::map<std::string, int> idNiveles);
		
		/**
		 * Destructor.
		 */
		virtual ~SelectorNiveles();

	private:
	
		Gtk::RadioButton** niveles;
		
		std::map<std::string, int> idNiveles;
};

#endif
