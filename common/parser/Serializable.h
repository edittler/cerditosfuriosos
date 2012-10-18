/* Interfaz para la serialización e hidratación de objetos
 */

#ifndef SERIALIZABLE_H_
#define SERIALIZABLE_H_

// Project Includes
#include "XMLTypes.h"

class Serializable {
public:

	Serializable();

	virtual ~Serializable();

	/* Serializa el objeto y retorna un nodo XML */
	virtual XMLNode serialize() = 0;

	/* A partir de un nodo XML se establece el objeto */
	virtual void hydrate(const XMLNode& nodo) = 0;
};

#endif /* SERIALIZABLE_H_ */
