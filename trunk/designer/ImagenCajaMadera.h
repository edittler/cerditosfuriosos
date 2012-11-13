#ifndef _IMAGEN_CAJA_MADERA_H_
#define _IMAGEN_CAJA_MADERA_H_
#include "ImagenPosicionable.h"

#define RUTA_CAJA_MADERA "imagenes/cajaMadera.png"
#define ANCHO_CAJA_MADERA 50;
#define ALTO_CAJA_MADERA 50;

/**
 * Las instancias de esta clase representan a la vista de una cada de madera
 * sobre un lienzo.
 */
class ImagenCajaMadera : public ImagenPosicionable {
	public:
		
		/**
		 * Constructor.
		 * @param x abscisa de la esquina superior derecha de la imagen
		 * @param y ordenada de la esquina superior derecha de la imagen
		 */
		ImagenCajaMadera(int x, int y);
		
		/**
		 * Destructor.
		 */
		virtual ~ImagenCajaMadera();
};

#endif
