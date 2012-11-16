#ifndef _IMAGEN_CERDO_H_
#define _IMAGEN_CERDO_H_
#include "ImagenPosicionable.h"
#include "ConstantesDiseniador.h"

/**
 * Las instancias de esta clase representan a la vista de un cerdo sobre un
 * lienzo.
 */
class ImagenCerdo : public ImagenPosicionable {
	public:
	
		/**
		 * Constructor.
		 * @param x abscisa de la esquina superior derecha de la imagen
		 * @param y ordenada de la esquina superior derecha de la imagen
		 */
		ImagenCerdo(int x, int y);
		
		/**
		 * Destructor.
		 */
		virtual ~ImagenCerdo();
};

#endif
