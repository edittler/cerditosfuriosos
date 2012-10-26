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

// Box2D Library Includes.
#include "Box2D/Box2D.h"

// Project Includes
#include "Serializable.h"
#include "CuerpoAbstracto.h"

/* Clase escenario. Contiene los objetos de la escena y ejecuta la simulacion.
 * Permite ser serializado e hidratado a partir de un nodo XML.
 */
class Escenario: public Serializable {
private:
	b2World* escenario;
	float tiempoTick;
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

	void correrTick();

	/* Agrega un Pajaro Rojo al mundo y lo lanza.
	 * @param posX posición inicial en el eje X.
	 * @param posY posición inicial en el eje Y.
	 * @param velocidad a la cual se va a realizar el lanzamiento.
	 * @param angulo al cual se va a realizar el lanzamiento.
	 */
	void lanzarPajaroRojo(int posX, int posY, int velocidad, int angulo);

	// Metodos para agregar superdicies
	void agregarCajaMadera(const int posX, const int posY);

private:
	void limpiarCuerposMuertos();
};

#endif /* ESCENARIO_H_ */