#ifndef _IMAGEN_HUEVOS_H_
#define _IMAGEN_HUEVOS_H_

// Hierarchy Includes.
#include "ImagenPosicionable.h"
#include "ImagenSerializable.h"

// Designer Project Includes.
#include "ConstantesDiseniador.h"

/**
 * Las instancias de esta clase representan a la vista de un monticulo de huevos
 * sobre un lienzo.
 */
class ImagenHuevos : public ImagenPosicionable, public ImagenSerializable {
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
	
	/**
	 * Serializa la imagen.
	 * @param alto del escenario en el que se va a serializar el objeto.
	 * @return nodo con el objeto serializado.
	 */
	XMLNode* serialize(const int altoEscenario) const;
};

#endif
