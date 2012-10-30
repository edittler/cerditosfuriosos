#ifndef _LIENZO_H_
#define _LIENZO_H_
#include <string>
#include <gtkmm/fixed.h>
#include <list>
#include "imagen_posicionable.h"

// Rutas de archivos con las imagenes de los objetos que integran el escenario
#define RUTA_CERDO "cerdo.png"
#define RUTA_HUEVOS "huevos.png"
#define RUTA_CAJA_MADERA "cajaMadera.png"
#define RUTA_CAJA_METAL "cajaMetal.png"

/**
 * Las instancias de esta clase representan a un contenedor vacio, sobre el cual
 * podemos arrastrar los objetos que integran el escenario del juego.
 */
class Lienzo : public Gtk::Fixed {
	public:
	
		Lienzo();
	
		virtual ~Lienzo();
	
	protected:
	
		void on_label_drop_drag_data_received(
								const Glib::RefPtr<Gdk::DragContext>& context,
								int x,
								int y,
								const Gtk::SelectionData& selection_data,
								guint info,
								guint time);
								
	private:
	
		//std::list<ImagenPosicionable*> posicionables;
};

#endif
