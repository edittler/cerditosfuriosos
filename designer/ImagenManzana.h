#ifndef _IMAGEN_MANZANA_H_
#define _IMAGEN_MANZANA_H_
#include "ImagenPosicionable.h"
#include "ConstantesDiseniador.h"

/**
 * Las instancias de esta clase representan a la vista de una manzana sobre un lienzo.
 */
class ImagenManzana : public ImagenPosicionable {
	public:
		
		/**
		 * Constructor.
		 * @param x abscisa de la esquina superior derecha de la imagen
		 * @param y ordenada de la esquina superior derecha de la imagen
		 */
		ImagenManzana(int x, int y);
		
		/**
		 * Destructor.
		 */
		virtual ~ImagenManzana();
};

#endif
