#ifndef HUEVORELOJ_H_
#define HUEVORELOJ_H_

// Hierarchy Include.
#include "Disparo.h"
#include "ObjetoVivo.h"

class HuevoReloj: public Disparo, public ObjetoVivo {
public:
	/* @brief Constructor con parámetros.
	 * @param body obtenido del World de Box2D.
	 * @param identificador del jugador que lanza el huevo.
	 * @param jugador que lanza el huevo.
	 */
	HuevoReloj(b2Body* body, unsigned int idJugador, Jugador* jugador,
			int milisegundos);

	// Destructor
	virtual ~HuevoReloj();

	/* @brief Serializa el Huevo Reloj y lo retorna en un nodo XML */
	XMLNode* serialize();

	/* @brief Como el CuerpoAbstracto requiere del b2Body para realizar
	 * operaciones básicas, no se puede hidratar desde un nodo, salvo algunos
	 * atributos.
	 */
	void hydrate(const XMLNode* nodo);

	// Metodo para el paso del tiempo
	void vivir(int milisegundos);

private:
	// Metodo que hace explotar el huevo.
	void explotar();

	/* @brief Hace crecer el huevo para que el danio tenga mayor alcance
	 */
	void aumentarTamanio();

	// Danio que le causa el cerdito.
	float danioCerdito;

	// Tiempo que tarda en explotar (en milisegundos)
	int tiempoExplosion;
};

#endif
