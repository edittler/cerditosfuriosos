#ifndef IMAGENFRUTA_H_
#define IMAGENFRUTA_H_

// Hierarchy Include.
#include "ImagenPosicionable.h"
#include "ImagenSerializable.h"

/**
 * Las instancias de esta clase representan a la vista de una fruta
 * sobre un lienzo.
 */
class ImagenFruta: public ImagenPosicionable, public ImagenSerializable {
public:
	/**
	 * Destructor.
	 */
	virtual ~ImagenFruta();

protected:
	/**
	 * Constructor.
	 * @param ruta donde se encuentra el archivo con la imagen.
	 */
	explicit ImagenFruta(const char* ruta);
};

#endif /* IMAGENFRUTA_H_ */
