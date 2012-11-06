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
using std::string;

/**
 * Las instancias de esta clase representan a un contenedor vacio, sobre el cual
 * podemos arrastrar los objetos que integran el escenario del juego.
 */
class Lienzo : public Gtk::Fixed {
	public:
	
		/**
		 * Constructor.
		 */
		Lienzo(int ancho, int alto);
	
		/**
		 * Destructor.
		 */
		virtual ~Lienzo();
		
		/**
		 * @param id identificador de la imagen contenida en este lienzo que se
		 * quiere eliminar
		 */
		void eliminarImagen(string id);
	
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
	
		list<Gtk::TargetEntry> listaObjetivos;
		list<ImagenPosicionable*> posicionables;
		
		/**
		 * Mueve el objeto identificado por el primer parametro hacia el punto,
		 * siempre y cuando no vaya a ocupar la posicion de otro objeto ya
		 * agregado ni a salirse de los limites.
		 * @param x abscisa donde queremos agregar a la imagen
		 * @param y ordenada donde queremos agregar a la imagen
		 */
		void moverObjeto(string id, int x, int y);
		
		/**
		 * @param x abscisa de la esquina superior derecha del objeto a agregar
		 * @param x ordenada de la esquina superior derecha del objeto a agregar
		 * @param imagen objeto a agregar
		 * @return true si el objeto a agregar coincidira espacialmente con
		 * alguno ya agregado y false en el caso contrario
		 */
		bool coincidenciaOcupacional(int x, int y, ImagenPosicionable* imagen);
		
		/**
		 * @param x abscisa de la esquina superior derecha del objeto a agregar
		 * @param x ordenada de la esquina superior derecha del objeto a agregar
		 * @param imagen objeto a agregar
		 * @return true si el objeto a agregar esta espacialmente dentro del
		 * escenario y false en el caso contrario
		 */
		bool dentroDeEscenario(int x, int y, ImagenPosicionable* imagen);
};

#endif
