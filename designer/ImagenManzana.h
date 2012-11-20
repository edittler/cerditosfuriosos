#ifndef _IMAGEN_MANZANA_H_
#define _IMAGEN_MANZANA_H_

// Hierarchy Include.
#include "ImagenFruta.h"

// Designer Project Includes.
#include "ConstantesDiseniador.h"

/**
 * Las instancias de esta clase representan a la vista de una manzana sobre un lienzo.
 */
class ImagenManzana : public ImagenFruta {
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

	/**
	 * Serializa la imagen.
	 * @param alto del escenario en el que se va a serializar el objeto.
	 * @return nodo con el objeto serializado.
	 */
	XMLNode* serialize(const int altoEscenario) const;
};

#endif
