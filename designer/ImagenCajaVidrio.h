#ifndef _IMAGEN_CAJA_VIDRIO_H_
#define _IMAGEN_CAJA_VIDRIO_H_
#include "ImagenPosicionable.h"

#define RUTA_CAJA_VIDRIO "imagenes/cajaVidrio.png"

/**
 * Las instancias de esta clase representan a la vista de una cada de vidrio
 * sobre un lienzo.
 */
class ImagenCajaVidrio : public ImagenPosicionable {
	public:
	
		/**
		 * Constructor.
		 * @param x abscisa de la esquina superior derecha de la imagen
		 * @param y ordenada de la esquina superior derecha de la imagen
		 */
		ImagenCajaVidrio(int x, int y);
		
		/**
		 * Destructor.
		 */
		virtual ~ImagenCajaVidrio();
};

#endif
