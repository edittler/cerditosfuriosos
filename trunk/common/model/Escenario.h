#ifndef ESCENARIO_H_
#define ESCENARIO_H_

// C++ Library Includes.
#include <list>

// Box2D Library Includes.
#include "Box2D/Box2D.h"

// Hierarchy Includes.
#include "EscenarioObservable.h"
#include "../parser/Serializable.h"

// Project Includes.
#include "CuerpoAbstracto.h" // FIXME Borrar luego de refactorizar
#include "Punto2D.h"
#include "Velocidad2D.h"
#include "Suelo.h"
#include "Jugador.h"
#include "Monticulo.h"
#include "Superficie.h"
#include "Fruta.h"
#include "Pajaro.h"
#include "Disparo.h"

/* @class Escenario.
 * Contiene los objetos de la escena y ejecuta la simulacion.
 * Permite ser serializado e hidratado a partir de un nodo XML.
 */
class Escenario: public EscenarioObservable, public Serializable {
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

	/*
	 * @brief Agrega la figura del suelo interpolando @param.
	 * El escenario solo puede contener un unico suelo. Al intentar agregar más,
	 * se lanzará excepcion.
	 * @param Lista de puntos para realizar la interpolacion
	 */
	void agregarSuelo(std::list<Punto2D*>& puntos);

	/* @brief Agrega al Cerdito con su respectiva Catapulta. Crea un jugador
	 * lo agrega a la lista de jugadores.
	 * @param Punto2D especificando la posición del Cerdito.
	 * @param Punto2D especificando la posición de la Catapulta.
	 */
	void agregarCerdito(Punto2D posCerdito, Punto2D posCatapulta);

	/* @brief Agrega el monticulo.
	 * El escenario puede contener un único monticulo de huevos. Al intentar
	 * agregar más, se lanzará excepciones.
	 * @param Punto2D especificando la posición del monticulo.
	 */
	void agregarMonticulo(Punto2D posMonticulo);

	/* @brief Agrega una Caja de Vidrio al escenario.
	 * @param Punto2D especificando la posición de la Caja de Vidrio.
	 */
	void agregarCajaVidrio(Punto2D posicion);

	/* @brief Agrega una Caja de Madera al escenario.
	 * @param Punto2D especificando la posición de la Caja de Madera.
	 */
	void agregarCajaMadera(Punto2D posicion);

	/* @brief Agrega una Caja de Metal al escenario.
	 * @param Punto2D especificando la posición de la Caja de Metal Vidrio.
	 */
	void agregarCajaMetal(Punto2D posicion);

	/* @brief Agrega una Manzana al escenario.
	 * @param Punto2D especificando la posición de la Manzana.
	 */
	void agregarManzana(Punto2D posicion);

	/* @brief Agrega una Banana al escenario.
	 * @param Punto2D especificando la posición de la Banana.
	 */
	void agregarBanana(Punto2D posicion);

	/* @brief Agrega una Cereza al escenario.
	 * @param Punto2D especificando la posición de la Cereza.
	 */
	void agregarCereza(Punto2D posicion);

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

	/* @brief Agrega un Pajaro Verde al escenario y lo lanza.
	 * @param Punto2D especificando la posición inicial del lanzamiento.
	 * @param Velocidad2D especificando la velocidad inicial del lanzamiento.
	 */
	void lanzarPajaroVerde(Punto2D posInicial, Velocidad2D velInicial);

	/* @brief Agrega un Pajaro Azul al escenario y lo lanza.
	 * @param Punto2D especificando la posición inicial del lanzamiento.
	 * @param Velocidad2D especificando la velocidad inicial del lanzamiento.
	 */
	void lanzarPajaroAzul(Punto2D posInicial, Velocidad2D velInicial);

	/* @brief Agrega un Huevo Blanco al escenario y lo lanza.
	 * @param Punto2D especificando la posición inicial del lanzamiento.
	 * @param Velocidad2D especificando la velocidad inicial del lanzamiento.
	 * @param Jugador que va a lanzar el disparo. Tiene que ser un valor mayor
	 * 			que 0.
	 */
	void lanzarHuevoBlanco(Punto2D posInicial, Velocidad2D velInicial,
			unsigned int jugador = 1);

	/* @brief Agrega unos Huevos de Codorniz al escenario y lo lanza.
	 * @param Punto2D especificando la posición inicial del lanzamiento.
	 * @param Velocidad2D especificando la velocidad inicial del lanzamiento.
	 * @param Jugador que va a lanzar el disparo. Tiene que ser un valor mayor
	 * 			que 0.
	 */
	void lanzarHuevosCodorniz(Punto2D posInicial, Velocidad2D velInicial,
			unsigned int jugador = 1);

	/* @brief Agrega un Huevo Poche al escenario y lo lanza.
	 * @param Punto2D especificando la posición inicial del lanzamiento.
	 * @param Velocidad2D especificando la velocidad inicial del lanzamiento.
	 * @param Jugador que va a lanzar el disparo. Tiene que ser un valor mayor
	 * 			que 0.
	 */
	void lanzarHuevoPoche(Punto2D posInicial, Velocidad2D velInicial,
			unsigned int jugador = 1);

	/* @brief Agrega un Huevo Reloj al escenario y lo lanza.
	 * @param Punto2D especificando la posición inicial del lanzamiento.
	 * @param Velocidad2D especificando la velocidad inicial del lanzamiento.
	 * @param Jugador que va a lanzar el disparo. Tiene que ser un valor mayor
	 * 			que 0.
	 */
	void lanzarHuevoReloj(Punto2D posInicial, Velocidad2D velInicial,
			unsigned int jugador = 1);

	/***********************
	 * GETTERS AND SETTERS *
	 ***********************/
	unsigned int getAlto() const;
	void setAlto(unsigned int alto);

	unsigned int getAncho() const;
	void setAncho(unsigned int ancho);

	std::string getRutaImagenFondo() const;
	void setRutaImagenFondo(std::string rutaArchivo);

private:
	Jugador* getJugador(unsigned int indice);
	void limpiarCuerposMuertos();
	void limpiarEnListas(CuerpoAbstracto* cuerpo);
	void notificarPosicionesAObservadores();
	void imprimirPosiciones();  // TODO, provisorio

	/**************
	 * ATTRIBUTES *
	 **************/
	/* Aunque no afecta al modelo y el comportamiento de los cuerpos que se
	 * incluyen en el escenario, se almacenan el ancho y alto del mismo
	 * que es establecido para usos externos (por ejemplo, la vista)
	 */
	int ancho;
	int alto;

	/* Al igual que el ancho y alto, el escenario tiene una imagen de fondo
	 * que se almacena para usos externos.
	 */
	std::string rutaImagenFondo;

	// Escenario de Box2D
	b2World* escenario;

	// Suelo del escenario
	Suelo* suelo;

	// Administrador de colisiones
	b2ContactListener* colisionador;

	// Lista de jugadores
	// FIXME implementar con std::vector, modificar metodo getJugador(i)
	// para que use jugadores.at, si hay exception out_of_range devolver NULL.
	std::list<Jugador*> jugadores;

	// Monticulo de huevos
	Monticulo* monticulo;

	/* Lista de superficies, frutas, pajaros y disparos que contiene el
	 * escenario.
	 */
	std::list<Superficie*> superficies;
	std::list<Fruta*> frutas;
	std::list<Pajaro*> pajaros;
	std::list<Disparo*> disparos;

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
