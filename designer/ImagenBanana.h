#ifndef _IMAGEN_BANANA_H_
#define _IMAGEN_BANANA_H_

// Hierarchy Include.
#include "ImagenFruta.h"

// Designer Project Includes.
#include "ConstantesDiseniador.h"

/**
 * Las instancias de esta clase representan a la vista de una banana
 * sobre un lienzo.
 */
class ImagenBanana : public ImagenFruta {
	public:
		
		/**
		 * Constructor.
		 * @param x abscisa de la esquina superior derecha de la imagen
		 * @param y ordenada de la esquina superior derecha de la imagen
		 */
		ImagenBanana(int x, int y);
		
		/**
		 * Destructor.
		 */
		virtual ~ImagenBanana();
};

#endif
