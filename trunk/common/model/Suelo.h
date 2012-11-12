#ifndef SUELO_H_
#define SUELO_H_

// C++ Library Includes
#include <list>

// Hierarchy Include.
#include "CuerpoAbstracto.h"

// Project Includes
#include "Punto2D.h"

class Suelo : public CuerpoAbstracto {
public:
	/* @brief Constructor que recibe el b2Body de Box2D.
	 */
	explicit Suelo(b2Body* body);

	// Destructor
	virtual ~Suelo();

	/* @brief Serializa el Suelo y lo retorna en un nodo XML */
	XMLNode* serialize();

	/* @brief Como el CuerpoAbstracto requiere del b2Body para realizar
	 * operaciones básicas, no se puede hidratar desde un nodo, salvo algunos
	 * atributos.
	 */
	void hydrate(const XMLNode* nodo);

	/*
	 * @brief Agrega punto para interpolacion.
	 * @param p Punto2D a agregar
	 */
	void agregarPunto(Punto2D p);

	/*
	 * @brief Elimina punto de interpolacion
	 * @param p Punto2D a eliminar.
	 */
	void borrarPunto(Punto2D p);

private:
	std::list<Punto2D*> puntos;
};

#endif /* SUELO_H_ */
