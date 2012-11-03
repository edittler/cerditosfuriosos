#ifndef CUERPOABSTRACTO_H_
#define CUERPOABSTRACTO_H_

// Box2D Library Includes.
#include "Box2D/Box2D.h"

// Project Includes.
#include "CuerpoObservable.h"

/* @class CuerpoAbstracto
 * Interfaz que define un cuerpo con una vida. Implementa el CuerpoObservable,
 * dado que los cuerpos que hereden de CuerpoAbstracto pueden ser vistos por
 * otros objetos mediante el patrón observador, por ejemplo, para la vista.
 */
class CuerpoAbstracto: public CuerpoObservable {
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

	/* @brief Cambia el estado del objeto a "muerto".
	 */
	void matar();

	/* @brief Notifica la posicion del cuerpo al observador.
	 */
	void notificarPosicionAObservador();

	Punto2D getPosicion();

	void printPosition() const; // TODO PROVISORIO, BORRAR

protected:
	b2Body* cuerpo;  // Cuerpo de Box2D que se encapsula.
	float vida;  // Vida del cuerpo.
};

#endif /* CUERPOABSTRACTO_H_ */
