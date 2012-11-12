#ifndef _CREADOR_MUNDO_H_
#define _CREADOR_MUNDO_H_

#include <gtkmm/paned.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/box.h>
#include <gtkmm/adjustment.h>

#include <map>
#include <string>

/**
 * Muestra un panel que le da al usuario la posibilidad de elegir un nombre y
 * una cantidad de jugadores para un nivel.
 */
class CreadorMundo : public Gtk::Paned {
	public:

		/**
		 * Constructor.
		 * @param nombreMundos contenedor mapa que permite acceder a los nombres
		 * de los mundos a partir de la ruta de su archivo
		 */
		CreadorMundo(std::map<std::string, std::string> nombreMundos);
		
		/**
		 * Destructor.
		 */
		virtual ~CreadorMundo();
		
		/**
		 * @return true si el nombre elegido para el mundo por el usuario no
		 * pertenece a otro (y no esta vacio) y false en el caso contrario
		 */
		bool nombreSeleccionadoValido();
	
	private:
		
		Gtk::Entry* nombre;
		Gtk::Adjustment* ajuste;
		Gtk::SpinButton* cantidadJugadores;
		std::map<std::string, std::string> nombreMundos;
};

#endif
