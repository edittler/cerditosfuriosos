#ifndef _CREADOR_NIVEL_H_
#define _CREADOR_NIVEL_H_

#include <gtkmm/paned.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/spinbutton.h>

/**
 * Muestra al usuario una caja combo que le permite optar por uno de los
 * tamanios predeterminados para el escenario del nivel, y un selector para que
 * opte por una duracion.
 */
class CreadorNivel : public Gtk::Paned {
	public:
	
		/**
		 * Constructor.
		 * @param idProximoNivel indice del proximo nivel dentro del mundo
		 */
		CreadorNivel(int idProximoNivel);
		
		/**
		 * Destructor.
		 */
		~CreadorNivel();
	
	private:
	
		Gtk::ComboBoxText selectorTamanio;
		Gtk::Adjustment* ajuste;
		Gtk::SpinButton* selectorDuracion;
		
		int idProximoNivel;
};

#endif
