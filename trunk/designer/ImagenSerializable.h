#ifndef IMAGENSERIALIZABLE_H_
#define IMAGENSERIALIZABLE_H_

// Common Project Includes.
#include "XMLTypes.h"

class ImagenSerializable {
public:
	ImagenSerializable() { }
	virtual ~ImagenSerializable() { }

	/* Serializa el objeto y retorna un nodo XML */
	virtual XMLNode* serialize(const int alto) const = 0;
};

#endif /* IMAGENSERIALIZABLE_H_ */
