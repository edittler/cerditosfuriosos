#ifndef ESCENARIO_H_
#define ESCENARIO_H_

// C++ Library Includes
#include <list>

// Box2D Library Includes.
#include "Box2D/Box2D.h"

// Project Includes
#include "Serializable.h"
#include "CuerpoAbstracto.h"
#include "Punto2D.h"
#include "Velocidad2D.h"
#include "Jugador.h"
//#include "MonticuloHuevos.h"

/* @class Escenario.
 * Contiene los objetos de la escena y ejecuta la simulacion.
 * Permite ser serializado e hidratado a partir de un nodo XML.
 */
class Escenario: public Serializable {
public:
	Escenario();
	virtual ~Escenario();

	/* @brief Serializa el escenario y retorna un nodo XML
	 * @return Devuelve el nodo XML serializado
	 */
	XMLNode serialize();

	/* @brief A partir de un nodo XML se establece el escenario
	 * @param recibe el nodo XML que contiene los datos del escenario
	 */
	void hydrate(const XMLNode& nodo);

	/* @brief Agrega al Cerdito con su respectiva Catapulta.
	 * @param Punto2D especificando la posición del Cerdito.
	 * @param Punto2D especificando la posición de la Catapulta.
	 */
	void agregarCerdito(Punto2D posCerdito, Punto2D posCatapulta);

	/* @brief Agrega una Caja de Madera al escenario.
	 * @param Punto2D especificando la posición de la Caja de Madera.
	 */
	void agregarCajaMadera(Punto2D posicion);

	/* @brief Habilita el escenario para iniciar la simulacion.
	 * Una vez habilitada la simulacion no se puede añadir más elementos
	 * estáticos como cajas, cerditos, catapultas y monticulo de huevos.
	 * Habilitar la simulacion permite lanzar pajaros y disparos.
	 * Lanza excepcion si el escenario no posee al menos un Cerdito (único
	 * jugador) o no posee el montículo de huevos.
	 */
	void habilitarSimulacion();

	/* @brief Corre un tick, generalmente 20 milisegundos.
	 */
	void correrTick();

	/* @brief Agrega un Pajaro Rojo al escenario y lo lanza.
	 * @param Punto2D especificando la posición inicial del lanzamiento.
	 * @param Velocidad2D especificando la velocidad inicial del lanzamiento.
	 */
	void lanzarPajaroRojo(Punto2D posInicial, Velocidad2D velInicial);

	/* @brief Agrega un Huevo Blanco al escenario y lo lanza.
	 * @param Punto2D especificando la posición inicial del lanzamiento.
	 * @param Velocidad2D especificando la velocidad inicial del lanzamiento.
	 * @param Jugador que va a lanzar el disparo. Tiene que ser un valor mayor
	 * 			que 0.
	 */
	void lanzarHuevoBlanco(Punto2D posInicial, Velocidad2D velInicial,
			unsigned int jugador = 1);

private:
	Jugador* getJugador(unsigned int indice);

	void limpiarCuerposMuertos();

	/**************
	 * ATTRIBUTES *
	 **************/

	// Escenario de Box2D
	b2World* escenario;

	// Administrador de colisiones
	b2ContactListener* colisionador;

	// Lista de jugadores
	std::list<Jugador*> jugadores;

	// Monticulo de huevos
//	MonticuloHuevos* monticulo;

	// Lista de objetos que contiene el World de Box2D
	std::list<CuerpoAbstracto*> objetos;

	/* Flag para indicar si la simulacion está habilitada.
	 * Si la simulacion no está habilitada, no se pueden lanzar pájaros
	 * ni disparos.
	 * Una vez habilitada la simulacion, no se puede añadir elementos estáticos
	 * como las cajas, frutas, cerditos, catapultas y monticulo de huevos.
	 */
	bool simulacionHabilitada;

	// Tiempo de tick (generalmente del orden de los 20 milisegundos)
	float tiempoTick;
};

#endif /* ESCENARIO_H_ */
