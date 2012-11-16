#ifndef _IMAGEN_CATAPULTA_H_
#define _IMAGEN_CATAPULTA_H_
#include "ImagenPosicionable.h"
#include "ConstantesDiseniador.h"

/**
 * Las instancias de esta clase representan a la vista de una catapulta sobre un
 * lienzo.
 */
class ImagenCatapulta : public ImagenPosicionable {
	public:
		
		/**
		 * Constructor.
		 * @param x abscisa de la esquina superior derecha de la imagen
		 * @param y ordenada de la esquina superior derecha de la imagen
		 */
		ImagenCatapulta(int x, int y);
		
		/**
		 * Destructor.
		 */
		virtual ~ImagenCatapulta();
};

#endif
