#ifndef IMAGENSUPERFICIE_H_
#define IMAGENSUPERFICIE_H_

// Hierarchy Include.
#include "ImagenPosicionable.h"

/**
 * Las instancias de esta clase representan a la vista de una superficie
 * sobre un lienzo.
 */
class ImagenSuperficie: public ImagenPosicionable {
public:
	/**
	 * Destructor.
	 */
	virtual ~ImagenSuperficie();

protected:
	/**
	 * Constructor.
	 * @param ruta donde se encuentra el archivo con la imagen.
	 */
	ImagenSuperficie(const char* ruta);
};

#endif /* IMAGENSUPERFICIE_H_ */
