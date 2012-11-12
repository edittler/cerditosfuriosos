#ifndef _SELECTOR_MUNDOS_H_
#define _SELECTOR_MUNDOS_H_

#include <gtkmm/scrolledwindow.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/box.h>

#include <map>
#include <string>

/**
 * Proporciona una ventana desplazable en la que hay un boton de radio por cada
 * mundo ya creado.
 */
class SelectorMundos : public Gtk::ScrolledWindow {
	public:
	
		/**
		 * Constructor.
		 * @param nombreMundos contenedor mapa que permite acceder a los nombres
		 * de los mundos a partir de la ruta de su archivo
		 */
		SelectorMundos(std::map<std::string, std::string> nombreMundos);
		
		/**
		 * Destructor.
		 */
		virtual ~SelectorMundos();
		
		/**
		 * @return nombre del nivel seleccionado
		 */
		std::string getNombreMundoSeleccionado();

	private:
	
		Gtk::RadioButton** mundos;
		std::map<std::string, std::string> nombreMundos;
};

#endif
