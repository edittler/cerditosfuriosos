#ifndef _IMAGEN_CAJA_MADERA_H_
#define _IMAGEN_CAJA_MADERA_H_

// Hierarchy Include.
#include "ImagenSuperficie.h"

// Designer Project Include.
#include "ConstantesDiseniador.h"

/**
 * Las instancias de esta clase representan a la vista de una cada de madera
 * sobre un lienzo.
 */
class ImagenCajaMadera : public ImagenSuperficie {
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
