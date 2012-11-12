#ifndef HUEVOBLANCO_H_
#define HUEVOBLANCO_H_

// Hierarchy Include.
#include "Disparo.h"

/* @class HuevoBlanco
 * Un tipo particular de disparo que se usa en el juego Cerditos Furiosos.
 */
class HuevoBlanco: public Disparo {
public:
	/* @brief Constructor con parámetros.
	 * @param body obtenido del World de Box2D.
	 * @param identificador del jugador que lanza el huevo.
	 * @param jugador que lanza el huevo.
	 */
	explicit HuevoBlanco(b2Body* body, unsigned int idJugador, Jugador* jugador);

	// Destructor
	virtual ~HuevoBlanco();

	/* @brief Serializa el Huevo Blanco y lo retorna en un nodo XML */
	XMLNode* serialize();

	/* @brief Como el CuerpoAbstracto requiere del b2Body para realizar
	 * operaciones básicas, no se puede hidratar desde un nodo, salvo algunos
	 * atributos.
	 */
	void hydrate(const XMLNode* nodo);
};

#endif /* HUEVOBLANCO_H_ */
