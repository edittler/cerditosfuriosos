#ifndef _CREADOR_MUNDO_H_
#define _CREADOR_MUNDO_H_

#include "ConstantesDiseniador.h"

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
		 * @return true si el usuario no ha elegido ningun nombre y false en el
		 * caso contrario
		 */
		bool nombreVacio();
		
		/**
		 * @return true si el nombre elegido para el mundo por el usuario
		 * pertenece a otro y false en el caso contrario
		 */
		bool nombreExistente();
		
		/**
		 * @return el nombre del mundo elegido por el usuario
		 */
		std::string getNombreElegido();

		/**
		 * @return la cantidad de jugadores elegida por el usuario
		 */
		int getCantidadJugadores();
	
	private:
		
		Gtk::Entry* nombre;
		Gtk::Adjustment* ajuste;
		Gtk::SpinButton* cantidadJugadores;
		std::map<std::string, std::string> nombreMundos;
};

#endif
