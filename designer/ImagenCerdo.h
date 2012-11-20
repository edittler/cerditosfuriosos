#ifndef _IMAGEN_CERDO_H_
#define _IMAGEN_CERDO_H_

// Hierarchy Includes.
#include "ImagenPosicionable.h"
#include "ImagenSerializable.h"

// Designer Project Includes.
#include "ConstantesDiseniador.h"

/**
 * Las instancias de esta clase representan a la vista de un cerdo sobre un
 * lienzo.
 */
class ImagenCerdo : public ImagenPosicionable, public ImagenSerializable {
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

	/**
	 * Serializa la imagen.
	 * @param alto del escenario en el que se va a serializar el objeto.
	 * @return nodo con el objeto serializado.
	 */
	XMLNode* serialize(const int altoEscenario) const;
};

#endif
