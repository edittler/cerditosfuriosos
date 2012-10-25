/*
 * Escenario.h
 *
 *  Created on: 24/10/2012
 *      Author: ezequiel
 */

#ifndef ESCENARIO_H_
#define ESCENARIO_H_

// C++ Library Includes
#include <list>

// Project Includes
#include "Serializable.h"
#include "Box2D/Box2D.h"
#include "CuerpoAbstracto.h"

/* Clase escenario. Contiene los objetos de la escena y ejecuta la simulacion.
 * Permite ser serializado e hidratado a partir de un nodo XML.
 */
class Escenario: public Serializable {
private:
	b2World* escenario;
	std::list<CuerpoAbstracto*> objetos;

public:
	Escenario();
	virtual ~Escenario();

	/* Serializa el escenario y retorna un nodo XML
	 * @return Devuelve el nodo XML serializado
	 */
	XMLNode serialize();

	/* A partir de un nodo XML se establece el escenario
	 * @param recibe el nodo XML que contiene los datos del escenario
	 */
	void hydrate(const XMLNode& nodo);

	void agregarCajaMadera(const unsigned int posX, const unsigned int posY);
};

#endif /* ESCENARIO_H_ */
