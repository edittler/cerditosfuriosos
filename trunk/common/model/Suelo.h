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
	Suelo(b2Body* body);
	virtual ~Suelo();

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
