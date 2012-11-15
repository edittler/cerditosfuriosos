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
		 * @param idNiveles contenedor mapa dentro del cual a partir del indice
		 * de un nivel se accede a la ruta de su archivo
		 */
		SelectorNiveles(std::map<int, std::string> idNiveles);
		
		/**
		 * Destructor.
		 */
		virtual ~SelectorNiveles();
		
		/**
		 * @return ruta del archivo del nivel seleccionado
		 */
		std::string getRutaNivelSeleccionado();

	private:
	
		Gtk::RadioButton** niveles;
		
		std::map<int, std::string> idNiveles;
};

#endif
