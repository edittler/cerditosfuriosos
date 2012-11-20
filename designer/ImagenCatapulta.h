#ifndef _IMAGEN_CATAPULTA_H_
#define _IMAGEN_CATAPULTA_H_

// Hierarchy Includes.
#include "ImagenPosicionable.h"
#include "ImagenSerializable.h"

// Designer Project Includes.
#include "ConstantesDiseniador.h"

/**
 * Las instancias de esta clase representan a la vista de una catapulta sobre un
 * lienzo.
 */
class ImagenCatapulta : public ImagenPosicionable, public ImagenSerializable {
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

	/**
	 * Serializa la imagen.
	 * @param alto del escenario en el que se va a serializar el objeto.
	 * @return nodo con el objeto serializado.
	 */
	XMLNode* serialize(const int altoEscenario) const;
};

#endif
