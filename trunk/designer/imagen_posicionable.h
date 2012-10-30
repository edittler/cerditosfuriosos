#ifndef _IMAGEN_POSICIONABLE_H_
#define _IMAGEN_POSICIONABLE_H_

#include <gtkmm/image.h>

/**
 * Las instancias de esta clase representan a imagenes que pueden colocarse en
 * un lienzo a traves de un drag and drop.
 */
class ImagenPosicionable : public Gtk::Image {
	private:
	
		/**
		 * Coordenadas del objeto en el lienzo que integra.
		 */
		int x, y;
		
	public:
	
		/**
		 * @param ruta donde se encuentra el archivo con la imagen
		 * @param x abscisa de la esquina superior derecha de la imagen
		 * @param y ordenada de la esquina superior derecha de la imagen
		 */
		ImagenPosicionable(const char* ruta, int x, int y);
		
		virtual ~ImagenPosicionable();
};

#endif
