#ifndef _CREADOR_NIVEL_H_
#define _CREADOR_NIVEL_H_

#include <gtkmm/paned.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>

#include <string>

#include "InformableSeleccion.h"

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
		 * @param informable se le informa cuando el usuario selecciona una
		 * informacion de relevancia
		 */
		CreadorNivel(int idProximoNivel, InformableSeleccion* informable);
		
		/**
		 * Destructor.
		 */
		~CreadorNivel();
	
	protected:
	
		void botonExaminarClickeado();
	
	private:
	
		Gtk::ComboBoxText selectorTamanio;
		Gtk::Adjustment* ajuste;
		Gtk::SpinButton* selectorDuracion;
		Gtk::Entry* archivoImagen;
		Gtk::Button* botonExaminar;
		
		InformableSeleccion* informable;
		int idProximoNivel;
};

#endif
