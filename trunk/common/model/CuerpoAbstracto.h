#ifndef CUERPOABSTRACTO_H_
#define CUERPOABSTRACTO_H_

// Box2D Library Includes.
#include "Box2D/Box2D.h"

class CuerpoAbstracto {
public:
	CuerpoAbstracto();
	virtual ~CuerpoAbstracto();

	/* @brief Retorna el estado del cuerpo
	 * @return true si el cuerpo esta vivo, false si esta muerto
	 */
	bool estaVivo() const;

	/* @brief Resta vida segun @param.
	 * @param Cantidad a restar.
	 */
	void daniar(float danio);

	/*
	 * @brief cambia el estado del objeto a "muerto".
	 */
	void matar();

	void printPosition() const; // TODO PROVISORIO, BORRAR

protected:
	b2Body* cuerpo;  // Cuerpo de Box2D que se encapsula.
	float vida;  // Vida del cuerpo.
};

#endif /* CUERPOABSTRACTO_H_ */
