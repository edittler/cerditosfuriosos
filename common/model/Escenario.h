#ifndef ESCENARIO_H_
#define ESCENARIO_H_

// C++ Library Includes.
#include <vector>
#include <map>
#include <string>

// Box2D Library Includes.
#include "Box2D/Box2D.h"

// Hierarchy Includes.
#include "EscenarioObservable.h"
#include "../parser/Serializable.h"

// Project Includes.
#include "Punto2D.h"
#include "Velocidad2D.h"
#include "Suelo.h"
#include "Jugador.h"
#include "Monticulo.h"
#include "Superficie.h"
#include "Fruta.h"
#include "Pajaro.h"
#include "Disparo.h"
#include "ObjetoVivo.h"
#include "Constantes.h"

// Thread Includes.
#include "../thread/Mutex.h"

/* @class Escenario.
 * Contiene los objetos de la escena y ejecuta la simulacion.
 * Permite ser serializado e hidratado a partir de un nodo XML.
 */
class Escenario: public EscenarioObservable, public Serializable {
public:
	/* @brief Constructor con parametros.
	 * @param Cantidad de jugadores que va a contener el escenario.
	 * Por defecto posee el valor 1.
	 */
	Escenario(unsigned int cantidadJugadores = 1);

	virtual ~Escenario();

	/* @brief Serializa el escenario y retorna un nodo XML
	 * @return Devuelve el nodo XML serializado
	 */
	XMLNode* serialize();

	/* @brief A partir de un nodo XML se establece el escenario
	 * @param recibe el nodo XML que contiene los datos del escenario
	 */
	void hydrate(const XMLNode* nodo);

	/* @brief Registra un observador.
	 * Solo permite registrar un único observador. En caso de querer agregar
	 * más, lanza excepciones.
	 * @param Observador a registrar.
	 */
	void registrarObservador(ObservadorEscenario* observador);

	/* @brief Elimina el observador especificado.
	 * En caso de que no exista el observador especificado lanza una excepcion.
	 */
	void eliminarObservador(ObservadorEscenario* observador);

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

	/* @brief Agrega un Huevo especifiando el tipo segun su probabilidad
	 * al escenario y lo lanza.
	 * @param Punto2D especificando la posición inicial del lanzamiento.
	 * @param Velocidad2D especificando la velocidad inicial del lanzamiento.
	 * @param Jugador que va a lanzar el disparo. Tiene que ser un valor mayor
	 * 			o igual que 0.
	 */
	void lanzarHuevo(Punto2D posInicial, Velocidad2D velInicial,
			unsigned int j);

	/* @brief Chequea que si la partida ha finalizado.
	 * @return true si la partida finalizo, false caso contrario.
	 */
	bool finalizoPartida() const;

	/* @brief Chequea si se gano la partida.
	 * @retun true si se gano la partida, false caso contrario.
	 */
	bool ganoPartida() const;

	/***********************
	 * GETTERS AND SETTERS *
	 ***********************/

	// FIXME return unsigned int pero alto y ancho son float, arreglar??
	void setTamanio(float ancho, float alto);
	float getAlto() const;
	float getAncho() const;

	std::string getRutaImagenFondo() const;
	void setRutaImagenFondo(std::string rutaArchivo);

	std::string getRutaImagenSuelo() const;
	void setRutaImagenSuelo(std::string rutaArchivo);

private:
	/***************************************************
	 * METODOS PRIVADOS DE SERIALIZACION E HIDRATACION *
	 ***************************************************/
	void XMLGuardarAtributos(XMLNode* nodoEscenario) const;
	XMLNode* XMLGetCerditos();
	XMLNode* XMLGetSuperficies();
	XMLNode* XMLGetFrutas();
	XMLNode* XMLGetPajaros();
	XMLNode* XMLGetDisparos();

	void XMLCargarAtributos(const XMLNode* nodo);
	void XMLCargarSuelo(const XMLNode* nodo);
	void XMLCargarCerditos(const XMLNode* nodo);
	void XMLCargarCerdito(const XMLNode* nodo);
	void XMLCargarMonticulo(const XMLNode* nodo);
	void XMLCargarSuperficies(const XMLNode* nodo);
	void XMLCargarFrutas(const XMLNode* nodo);
	void XMLCargarPajaros(const XMLNode* nodo);
	void XMLCargarDisparos(const XMLNode* nodo);

	/*********************************************************
	 * METODOS PRIVADOS DE OPERACIONES INTERNAS DE ESCENARIO *
	 *********************************************************/
	Jugador* getJugador(unsigned int indice);
	/*
	 * @brief Valida que haya cerditos vivos, y elimina aquellos muertos.
	 * @return true si existe algun cerdito vivo, false en caso contrario.
	 */
	bool validarCerditosVivos();
	void limpiarCuerposInvalidos();
	void notificarPosicionesAObservadores();

	// Metodos privados segun el tipo de huevo a lanzar.
	void lanzarHuevoBlanco(Punto2D posInicial, Velocidad2D velInicial,
			unsigned int id, Jugador* jugador);
	void lanzarHuevosCodorniz(Punto2D posInicial, Velocidad2D velInicial,
			unsigned int id, Jugador* jugador);
	void lanzarHuevoPoche(Punto2D posInicial, Velocidad2D velInicial,
			unsigned int id, Jugador* jugador);
	void lanzarHuevoReloj(Punto2D posInicial, Velocidad2D velInicial,
			unsigned int id, Jugador* jugador);

	/**************
	 * ATTRIBUTES *
	 **************/
	/* Aunque no afecta al modelo y el comportamiento de los cuerpos que se
	 * incluyen en el escenario, se almacenan el ancho y alto del mismo
	 * que es establecido para usos externos (por ejemplo, la vista)
	 */
	float ancho;
	float alto;

	/* Al igual que el ancho y alto, el escenario tiene una imagen de fondo
	 * que se almacena para usos externos.
	 */
	std::string rutaImagenFondo;
	std::string rutaImagenSuelo;

	/* Cantidad de jugadores para el cual se va a diseñar el escenario.
	 */
	unsigned int cantJugadores;

	/* Flag para indicar si la simulacion está habilitada.
	 * Si la simulacion no está habilitada, no se pueden lanzar pájaros
	 * ni disparos.
	 * Una vez habilitada la simulacion, no se puede añadir elementos estáticos
	 * como las cajas, frutas, cerditos, catapultas y monticulo de huevos.
	 */
	bool simulacionHabilitada;

	// flag que indica si la partida finalizo.
	bool finalizo;

	// tiempo de juego. En milisegundos.
	unsigned int tiempoDeJuego;
	// duracion de juego. En milisegundos.
	unsigned int duracionDeJuego;

	ObservadorEscenario* observador;

	// Escenario de Box2D
	b2World* escenario;

	// Administrador de colisiones
	b2ContactListener* colisionador;

	// Suelo del escenario
	Suelo* suelo;

	// Lista de jugadores
	std::vector<Jugador*> jugadores;

	// Mutex para la lista de jugadores
	Mutex mJugadores;

	// Monticulo de huevos
	Monticulo* monticulo;

	/* Lista de superficies, frutas, pajaros y disparos que contiene el
	 * escenario.
	 */
	std::list<Superficie*> superficies;
	std::list<Fruta*> frutas;
	std::list<Pajaro*> pajaros;
	std::list<Disparo*> disparos;
	std::list<ObjetoVivo*> objetosVivos;

	// Mutex de las listas de cuerpos.
	Mutex mSuperficies;
	Mutex mFrutas;
	Mutex mPajaros;
	Mutex mDisparos;
	Mutex mObjetosVivos;

	/*********************
	 * PARSER ATTRIBUTES *
	 *********************/
	// Definicion de valores para superficies
	static enum SuperficieValues {
		supNoDefinida,
		supCajaVidrio,
		supCajaMadera,
		supCajaMetal
	} supValues;

	// Definición del mapa de superficies
	typedef std::map<std::string, SuperficieValues> SuperficiesMap;

	// Mapa asociado a los strings de valores enumerados de Superficies.
	static SuperficiesMap mapSuperficies;

	// Definicion de valores para frutas
	static enum FrutasValues {
		fruNoDefinida,
		fruManzana,
		fruBanana,
		fruCereza
	} fruValues;

	// Definición del mapa de frutas
	typedef std::map<std::string, FrutasValues> FrutasMap;

	// Mapa asociado a los strings de valores enumerados de Frutas.
	static FrutasMap mapFrutas;

	// Definicion de valores para pajaros
	static enum PajarosValues {
		pajNoDefinido,
		pajPajaroRojo,
		pajPajaroVerde,
		pajPajaroAzul
	} pajValues;

	// Definición del mapa de pajaros
	typedef std::map<std::string, PajarosValues> PajarosMap;

	// Mapa asociado a los strings de valores enumerados de Pajaros.
	static PajarosMap mapPajaros;

	// Definicion de valores para disparos
	static enum DisparosValues {
		disNoDefinido,
		disHuevoBlanco,
		disHuevoCodorniz,
		disHuevoPoche,
		disHuevoReloj
	} disValues;

	// Definición del mapa de disparos
	typedef std::map<std::string, DisparosValues> DisparosMap;

	// Mapa asociado a los strings de valores enumerados de Disparos.
	static DisparosMap mapDisparos;

	/*************************************************
	 * Funciones privadas para inicializar los mapas *
	 *************************************************/
	static SuperficiesMap inicializarMapaSuperficies();
	static FrutasMap inicializarMapaFrutas();
	static PajarosMap inicializarMapaPajaros();
	static DisparosMap inicializarMapaDisparos();
};

#endif /* ESCENARIO_H_ */
