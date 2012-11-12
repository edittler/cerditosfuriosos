#ifndef HUEVOPOCHE_H_
#define HUEVOPOCHE_H_

// Hierarchy Include.
#include "Disparo.h"

class HuevoPoche: public Disparo {
public:
	/* @brief Constructor con parámetros.
	 * @param body obtenido del World de Box2D.
	 * @param identificador del jugador que lanza el huevo.
	 * @param jugador que lanza el huevo.
	 */
	HuevoPoche(b2Body* body, unsigned int idJugador, Jugador* jugador);

	// Destructor
	virtual ~HuevoPoche();

	/* @brief Serializa el Huevo Poche y lo retorna en un nodo XML */
	XMLNode* serialize();

	/* @brief Como el CuerpoAbstracto requiere del b2Body para realizar
	 * operaciones básicas, no se puede hidratar desde un nodo, salvo algunos
	 * atributos.
	 */
	void hydrate(const XMLNode* nodo);
};

#endif /* HUEVOPOCHE_H_ */
