#ifndef HUEVOCODORNIZ_H_
#define HUEVOCODORNIZ_H_

// Hierarchy Include.
#include "Disparo.h"

class HuevoCodorniz: public Disparo {
public:
	/* @brief Constructor con parámetros.
	 * @param body obtenido del World de Box2D.
	 * @param identificador del jugador que lanza el huevo.
	 * @param jugador que lanza el huevo.
	 */
	HuevoCodorniz(b2Body* body, unsigned int idJugador, Jugador* jugador);

	// Destructor
	virtual ~HuevoCodorniz();

	/* @brief Serializa el Huevo de Codorniz y lo retorna en un nodo XML */
	XMLNode* serialize();

	/* @brief Como el CuerpoAbstracto requiere del b2Body para realizar
	 * operaciones básicas, no se puede hidratar desde un nodo, salvo algunos
	 * atributos.
	 */
	void hydrate(const XMLNode* nodo);
};

#endif /* HUEVOCODORNIZ_H_ */
