#ifndef _IMAGEN_POSICIONABLE_H_
#define _IMAGEN_POSICIONABLE_H_
#include <gtkmm/image.h>
#include <gtkmm/eventbox.h>

#include <list>
#include <string>

/**
 * Las instancias de esta clase representan a imagenes que pueden colocarse en
 * un lienzo a traves de un drag and drop.
 */
class ImagenPosicionable : public Gtk::EventBox {
	public:
	
		/**
		 * Destructor.
		 */
		virtual ~ImagenPosicionable();
		
		/**
		 * Devuelve un string que identifica univocamente a esta instancia.
		 */
		virtual std::string getId();
		
		/**
		 * @return abscisa de la esquina superior derecha de la imagen
		 */
		virtual int getX();
		
		/**
		 * @return ordenada de la esquina superior derecha de la imagen
		 */
		virtual int getY();
		
		/**
		 * @param x abscisa de la esquina superior derecha de la imagen
		 */
		virtual void setX(int x);
		
		/**
		 * @param y ordenada de la esquina superior derecha de la imagen
		 */
		virtual void setY(int y);
		
		// Dimensiones de la imagen en pixeles
		int alto;
		int ancho;
	
	protected:
	
		/**
		 * Constructor.
		 * @param ruta donde se encuentra el archivo con la imagen
		 */
		ImagenPosicionable(const char* ruta);
	
		/**
		 * Coordenadas del objeto en el lienzo que integra.
		 */
		int x, y;
		
		/* Un identificador unico para cada instancia de esta clase o una
		 * subclase de la misma. */
		std::string id;
		
		/* Lleva una cuenta de la cantidad de instancias de esta clase (y de sus
		 * subclases) que se crean, para darle a cada una un identificador. */		
		static int contadorInstancias;
		
		void imagen_arrastrada(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time);
};

#endif
