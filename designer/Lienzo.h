#ifndef _LIENZO_H_
#define _LIENZO_H_
#include <string>
#include <gtkmm/fixed.h>
#include <gtkmm/eventbox.h>
#include <list>
#include "ImagenCajaMadera.h"
#include "ImagenCajaMetal.h"
#include "ImagenCajaVidrio.h"
#include "ImagenCerdo.h"
#include "ImagenHuevos.h"


using std::list;

/**
 * Las instancias de esta clase representan a un contenedor vacio, sobre el cual
 * podemos arrastrar los objetos que integran el escenario del juego.
 */
class Lienzo : public Gtk::Fixed {
	public:
	
		/**
		 * Constructor.
		 */
		Lienzo();
	
		/**
		 * Destructor.
		 */
		virtual ~Lienzo();
	
	protected:
	
		/**
		 * Recibe informacion de un drag and drop e instancia una imagen
		 * posicionable en funcion de esta.
		 */
		void recibirInformacion(
								const Glib::RefPtr<Gdk::DragContext>& context,
								int x,
								int y,
								const Gtk::SelectionData& selection_data,
								guint info,
								guint time);
								
	private:
	
		list<ImagenPosicionable*> posicionables;
};

#endif
