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

/* Clase escenario. Contiene los objetos de la escena y ejecuta la simulacion.
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

	/* Agrega al Cerdito con su respectiva Catapulta.
	 * @param Punto2D especificando la posición del Cerdito.
	 * @param Punto2D especificando la posición de la Catapulta.
	 */
	int agregarCerdito(Punto2D posCerdito, Punto2D posCatapulta);

	/* @brief Agrega una Caja de Madera al escenario.
	 * @param Punto2D especificando la posición de la Caja de Madera.
	 */
	void agregarCajaMadera(Punto2D posicion);

	/* Habilita el escenario para iniciar la simulacion.
	 * Una vez iniciada la simulacion no se puede añadir más elementos estáticos
	 * como cajas, frutas, cerditos, catapultas y monticulo de huevos.
	 * Habilitar la simulacion permite lanzar pajaros y disparos.
	 * Lanza excepcion si el escenario no posee al menos un Cerdito (único
	 * jugador) o no posee el montículo de huevos.
	 */
	void comenzarSimulacion();

	/* Corre un tick, generalmente 20 milisegundos.
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
	 */
	void lanzarHuevoBlanco(Punto2D posInicial, Velocidad2D velInicial);

private:
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

	/* Flag para indicar si comenzo la simulacion.
	 * Si la simulacion no comenzo, no se pueden lanzar pájaros ni disparos.
	 * Una vez comenzada la simulacion, no se puede añadir elementos estáticos
	 * como las cajas, frutas, cerditos, catapultas.
	 */
	bool comenzoSimulacion;

	// Tiempo de tick (generalmente del orden de los 20 milisegundos)
	float tiempoTick;
};

#endif /* ESCENARIO_H_ */
