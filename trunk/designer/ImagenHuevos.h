#ifndef _IMAGEN_HUEVOS_H_
#define _IMAGEN_HUEVOS_H_
#include "ImagenPosicionable.h"

#define RUTA_HUEVOS "imagenes/huevos.png"
#define ALTO_HUEVOS 60
#define ANCHO_HUEVOS 60

/**
 * Las instancias de esta clase representan a la vista de un monticulo de huevos
 * sobre un lienzo.
 */
class ImagenHuevos : public ImagenPosicionable {
	public:
	
		/**
		 * Constructor.
		 * @param x abscisa de la esquina superior derecha de la imagen
		 * @param y ordenada de la esquina superior derecha de la imagen
		 */
		ImagenHuevos(int x, int y);
		
		/**
		 * Destructor.
		 */
		virtual ~ImagenHuevos();
};

#endif
