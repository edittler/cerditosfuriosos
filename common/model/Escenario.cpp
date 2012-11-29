// C++ Library Includes.
#include <sstream>
#include <stdexcept>

// Project Includes
#include "Escenario.h"
#include "Colisionador.h"
#include "Jugador.h"
#include "Suelo.h"

// Superficies Includes.
#include "CajaVidrio.h"
#include "CajaMadera.h"
#include "CajaMetal.h"

// Pajaros Include.
#include "PajaroRojo.h"
#include "PajaroVerde.h"
#include "PajaroAzul.h"

// Disparos Include.
#include "HuevoBlanco.h"
#include "HuevoCodorniz.h"
#include "HuevoPoche.h"
#include "HuevoReloj.h"

// Other Objects Includes.
#include "Cerdito.h"
#include "Catapulta.h"

// Exceptions Includes.
#include "exceptions/ParserException.h"
#include "exceptions/ObservadorException.h"
#include "exceptions/AgregarObjetoException.h"
#include "exceptions/SimulacionException.h"
#include "exceptions/NoExisteJugadorException.h"

// Thread Includes.
#include "../thread/Lock.h"

Escenario::Escenario(unsigned int cantidadJugadores) {
	// Inicializo los atributos de dimensiones.
	this->ancho = 0;
	this->alto = 0;
	// Inicializo la cantidad de jugadores que va a tener el escenario
	this->cantJugadores = cantidadJugadores;
	// Defino que la simulacion no comenzo
	this->simulacionHabilitada = false;
	// Establezco el observadro, suelo y monticulo como NULL.
	this->observador = NULL;
	this->suelo = NULL;
	this->monticulo = NULL;

	// Creo el mundo
	b2Vec2 gravity(GRAVEDAD_X, GRAVEDAD_Y);  // Vector que indica la gravedad
	this->escenario = new b2World(gravity);

	// Agrego el ContactListener
	this->colisionador = new Colisionador();
	this->escenario->SetContactListener(this->colisionador);

	this->finalizo = false;
	this->tiempoDeJuego = 0;
	this->duracionDeJuego = 10 * 1000;  // FIXME cargar desde XML, se cuenta en milisegundos.
}

Escenario::~Escenario() {
	// Inhabilito la simulacion y doy por finalizada la partida.
	// Libero la memoria del escenario de Box2D
	delete this->escenario;
	// Libero la memoria del colisionador
	delete this->colisionador;
	// Libero la memoria de los jugadores
	Lock(this->mJugadores);
	std::vector<Jugador*>::iterator itJ;
	for(itJ = this->jugadores.begin(); itJ != this->jugadores.end(); ++itJ) {
		delete (*itJ);
	}
	// Libero la memoria de los objetos
	Lock(this->mSuperficies);
	std::list<Superficie*>::iterator itSup;
	for(itSup = superficies.begin(); itSup != superficies.end(); ++itSup) {
		delete (*itSup);
	}
	Lock(this->mFrutas);
	std::list<Fruta*>::iterator itFru;
	for(itFru = frutas.begin(); itFru != frutas.end(); ++itFru) {
		delete (*itFru);
	}
	Lock(this->mPajaros);
	std::list<Pajaro*>::iterator itPaj;
	for(itPaj = pajaros.begin(); itPaj != pajaros.end(); ++itPaj) {
		delete (*itPaj);
	}
	Lock(this->mDisparos);
	std::list<Disparo*>::iterator itDis;
	for(itDis = disparos.begin(); itDis != disparos.end(); ++itDis) {
		delete (*itDis);
	}
	// Libero la memoria del monticulo
	if (this->monticulo != NULL)
		delete this->monticulo;
	// Libero la memoria del Suelo
	if (this->suelo != NULL)
		delete this->suelo;
}

XMLNode* Escenario::serialize() {
	// Creo el nodo para almacenar el escenario
	XMLNode* nodo = new XMLNode("Escenario");
	// Almaceno los atributos en el nodo del escenario
	this->XMLGuardarAtributos(nodo);
	// Almaceno el suelo.
	nodo->LinkEndChild(this->suelo->serialize());
	// Almaceno la lista de cerditos.
	nodo->LinkEndChild(this->XMLGetCerditos());
	// Almaceno el monticulo de huevos
	nodo->LinkEndChild(this->monticulo->serialize());
	// Almaceno la lista de superficies
	nodo->LinkEndChild(this->XMLGetSuperficies());
	// Almaceno la lista de frutas
	nodo->LinkEndChild(this->XMLGetFrutas());
	/* Si la simulación se encuentra habilitada y se desea serializar el objeto,
	 * es porque se va a usar el archivo XML para reanudar partidas.
	 * Entonces, agrego los nodos correspondientes a Pajaros y Disparos.
	 */
	if (this->simulacionHabilitada) {
		// Almaceno la lista de pajaros
		nodo->LinkEndChild(this->XMLGetPajaros());
		// Almaceno la lista de disparos
		nodo->LinkEndChild(this->XMLGetDisparos());
	}
	// Retorno el nodo del escenario
	return nodo;
}

void Escenario::hydrate(const XMLNode* nodo) {
	// Obtengo el nombre del nodo
	std::string nombre = nodo->ValueStr();
	/* Comparo el nombre obtenido con el que se requiere.
	 * Si no es igual, lanzo una excepcion.
	 */
	if (nombre.compare("Escenario") != 0) {
		throw ParserException("El nodo Escenario es incorrecto.");
	}
	// Cargo los atributos
	this->XMLCargarAtributos(nodo);
	/* TODO(eze) Se deberia cargar el suelo desde el XML, pero como no está
	 * implementado, lo creo aca.
	 */
	std::list<Punto2D*> puntosSuelo;
	this->agregarSuelo(puntosSuelo);
	// Obtengo el nodo de Cerditos y los cargo.
	const XMLNode* cerditos = nodo->FirstChildElement("Cerditos");
	// Si no existe el nodo Cerditos, lanzo una excepcion
	if (cerditos == 0) {
		throw ParserException("El nodo Escenario no contiene el nodo con los"
				"cerditos.");
	}
	this->XMLCargarCerditos(cerditos);
	// Obtengo el nodo del montíluco de huevos y lo cargo.
	const XMLNode* monticulo = nodo->FirstChildElement("MonticuloHuevos");
	// Si no existe el nodo MonticuloHuevos, lanzo una excepcion
	if (monticulo == 0) {
		throw ParserException("El nodo Escenario no contiene el nodo con el"
				"Montículo de Huevos.");
	}
	this->XMLCargarMonticulo(monticulo);
	// Obtengo el nodo de las Superficies y las cargo.
	const XMLNode* superficies = nodo->FirstChildElement("Superficies");
	// Si no existe el nodo Superficies, lanzo una excepcion
	if (superficies == 0) {
		throw ParserException("El nodo Escenario no contiene el nodo con las"
				"superficies.");
	}
	this->XMLCargarSuperficies(superficies);
	// Obtengo el nodo de las Frutas y las cargo.
	const XMLNode* frutas = nodo->FirstChildElement("Frutas");
	// Si no existe el nodo Frutas, lanzo una excepcion
	if (frutas == 0) {
		throw ParserException("El nodo Escenario no contiene el nodo con las"
				"frutas.");
	}
	this->XMLCargarFrutas(frutas);
	/* Una vez cargados todos estos elementos, procedo a habilitar la
	 * simulacion.
	 */
	this->habilitarSimulacion();
	std::cout << "\t=== SIMULACION HABILITADA ===" << std::endl;
	/* Para el caso de recuperación de partida, se deben cargar los nodos de
	 * pájaros y disparos. Estos nodos no se encuentran obligaroriamente en
	 * el archivo XML, por lo que no lanzo excepcion en caso de que no se
	 * encuentren.
	 */
	// Obtengo el nodo de los Pájaros y los cargo.
	const XMLNode* pajaros = nodo->FirstChildElement("Pajaros");
	// Si existe el nodo Pajaros, los cargo al escenario
	if (pajaros != 0) {
		this->XMLCargarPajaros(pajaros);
	}
	// Obtengo el nodo de los Disparos y los cargo.
	const XMLNode* disparos = nodo->FirstChildElement("Disparos");
	// Si existe el nodo Disparos, los cargo al escenario
	if (disparos != 0) {
		this->XMLCargarDisparos(disparos);
	}
}

void Escenario::registrarObservador(ObservadorEscenario* observador) {
	/* Si el observador no es nulo, es porque ya hay uno registrado. Como no
	 * puede haber más de un observador, lanzo una excepcion.
	 */
	if (this->observador != NULL) {
		throw ObservadorException("El objeto ya tiene un observador.");
	}
	this->observador = observador;
}

void Escenario::eliminarObservador(ObservadorEscenario* observador) {
	/* Si el observador que se quiere eliminar no coincide con el que se
	 * encuentra registrado, lanzo una excepcion.
	 */
	if (this->observador != observador) {
		throw ObservadorException("El observador no se encuentra registrado.");
	}
	this->observador = NULL;
}

void Escenario::agregarSuelo(std::list<Punto2D*>& puntos) {
	/* TODO implementar, el codigo siguiente no utilza @puntos para
	 * hacer la interpolacion de puntos. Solo crea un suelo rectangular-
	 */

	// Valido que se haya creado un suelo anteriormente.
	if (this->suelo != NULL) {
		throw AgregarObjetoException("Ya existe un suelo, no se puede agregar"
				" uno nuevo");
	}

	// Defino el cuerpo del suelo.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(ancho / 2, SUELO_POSICION);
	// Creo el cuerpo del suelo.
	b2Body* groundBody = this->escenario->CreateBody(&groundBodyDef);

	Suelo* suelo = new Suelo(groundBody, ancho, SUELO_ALTO);
	this->suelo = suelo;
}

void Escenario::agregarCerdito(Punto2D posCerdito, Punto2D posCatapulta,
		unsigned int idJugador) {
	/* Solo puedo agregar un cerdito y su catapulta si la simulación no ha
	 * comenzado. Si la simulacion ya comenzo, lanzo una excepcion
	 */
	if (this->simulacionHabilitada) {
		throw AgregarObjetoException("La simulación esta corriendo, no se puede"
				" agregar Cerdito.");
	}
	/* Verifica si la cantidad de jugadores ya alcanza a la cantidad requerida
	 * por el escenario. Si es igual a la cantidad requerida, no se puede
	 * agregar el cerdito y lanza excepcion.
	 */
	Lock(this->mJugadores);
	if (this->jugadores.size() >= this->cantJugadores) {
		throw AgregarObjetoException("El escenario ya posee la cantidad de "
				"jugadores requeridos, no se puede agregar Cerdito.");
	}
	/* El cerdito tiene asociado una catapulta. Creo la catapulta primero para
	 * luego añadirla al cerdito.
	 */
	// Defino el cuerpo de la catapulta, seteo el tipo y la posicion y la creo.
	b2BodyDef bodyCatapultaDef;
	bodyCatapultaDef.type = b2_staticBody;
	bodyCatapultaDef.position.Set(posCatapulta.x, posCatapulta.y);
	b2Body* bodyCatapulta = this->escenario->CreateBody(&bodyCatapultaDef);
	// Creo el objeto Catapulta y le paso el cuerpo de Box2D
	Catapulta* catapulta = new Catapulta(bodyCatapulta);
	// Defino el cuerpo del cerdito, seteo el tipo y la posicion y lo creo.
	b2BodyDef bodyCerditoDef;
	bodyCerditoDef.type = b2_staticBody;
	bodyCerditoDef.position.Set(posCerdito.x, posCerdito.y);
	b2Body* bodyCerdito = this->escenario->CreateBody(&bodyCerditoDef);
	// Creo el objeto Cerdito y le paso el cuerpo de Box2D y la catapulta
	Cerdito* cerdito = new Cerdito(bodyCerdito, catapulta);
	/* El cerdito está asociado a un jugador.
	 * Creo dicho jugador y le paso el cerdito.
	 */
	Jugador* jugador = new Jugador(cerdito, idJugador);
	// Agrego el jugador en la lista de jugadores.
	this->jugadores.push_back(jugador);
	/* No agrego al cerdito en la lista de objetos porque lo administra y
	 * liberará su memoria el jugador asociado
	 */
	// Notifico al observador se que agrego un cerdito
	if (this->observador != NULL) {
		this->observador->seAgregoCerdito(cerdito);
		this->observador->seAgregoCatapulta(catapulta);
	}
}

void Escenario::agregarMonticulo(Punto2D posMonticulo) {
	/* Solo puedo agregar un monticulo si la simulación no ha
	 * comenzado. Si la simulacion ya comenzo, lanzo una excepcion
	 */
	if (this->simulacionHabilitada) {
		throw AgregarObjetoException("La simulación esta corriendo, no se puede"
				" agregar monticulo.");
	}
	/* El escenario solo puede contener un solo montículo. Si se desea agregar
	 * más, se lanzara excepciones.
	 */
	if (this->monticulo != NULL) {
		throw AgregarObjetoException("El escenario ya posee un monticulo de"
				"huevos");
	}
	// Defino el cuerpo del monticulo, seteo el tipo y la posicion y lo creo.
	b2BodyDef bodyMonticuloDef;
	bodyMonticuloDef.type = b2_staticBody;
	bodyMonticuloDef.position.Set(posMonticulo.x, posMonticulo.y);
	b2Body* bodyMonticulo = this->escenario->CreateBody(&bodyMonticuloDef);

	// Creo el objeto Monticulo y le paso el cuerpo de Box2D
	Monticulo* monticulo = new Monticulo(bodyMonticulo);
	this->monticulo = monticulo;
	// Notifico al observador se que agrego un monticulo
	if (this->observador != NULL) {
		this->observador->seAgregoMonticulo(monticulo);
	}
}

void Escenario::agregarCajaVidrio(Punto2D p) {
	/* Solo puedo agregar una Caja de vidrio si la simulación no ha comenzado.
	 * Si la simulacion ya comenzo, lanzo una excepcion
	 */
	if (this->simulacionHabilitada) {
		throw AgregarObjetoException("La simulación esta corriendo, no se puede"
				" agregar Caja de Vidrio.");
	}

	// Defino el cuerpo, seteo el tipo y la posicion y luego lo creo
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(p.x, p.y);
	b2Body* body = this->escenario->CreateBody(&bodyDef);

	// Creo el objeto CajaVidrio y le paso el cuerpo de Box2D
	CajaVidrio* cajaVidrio = new CajaVidrio(body);

	// Bloqueo la lista de superficies y agrego la caja de vidrio.
	Lock(this->mSuperficies);
	this->superficies.push_back(cajaVidrio);

	// Notifico al observador que se creo una caja.
	if (this->observador != NULL) {
		this->observador->seAgregoCajaVidrio(cajaVidrio);
	}
}

void Escenario::agregarCajaMadera(Punto2D p) {
	/* Solo puedo agregar una Caja de Madera si la simulación no ha comenzado.
	 * Si la simulacion ya comenzo, lanzo una excepcion
	 */
	if (this->simulacionHabilitada) {
		throw AgregarObjetoException("La simulación esta corriendo, no se puede"
				" agregar Caja de Madera.");
	}
	// Defino el cuerpo, seteo el tipo y la posicion y luego lo creo
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(p.x, p.y);
	b2Body* body = this->escenario->CreateBody(&bodyDef);
	// Creo el objeto CajaMadera y le paso el cuerpo de Box2D
	CajaMadera* cajaMadera = new CajaMadera(body);

	// Bloqueo la lista de superficies y agrego la caja.
	Lock(this->mSuperficies);
	this->superficies.push_back(cajaMadera);
	// Notifico al observador que se creo una caja de madera.
	if (this->observador != NULL)
		this->observador->seAgregoCajaMadera(cajaMadera);
}

void Escenario::agregarCajaMetal(Punto2D p) {
	/* Solo puedo agregar una Caja de metal si la simulación no ha comenzado.
	 * Si la simulacion ya comenzo, lanzo una excepcion
	 */
	if (this->simulacionHabilitada) {
		throw AgregarObjetoException("La simulación esta corriendo, no se puede"
				" agregar Caja de Metal.");
	}

	// Defino el cuerpo, seteo el tipo y la posicion y luego lo creo
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(p.x, p.y);
	b2Body* body = this->escenario->CreateBody(&bodyDef);

	// Creo el objeto CajaMetal y le paso el cuerpo de Box2D
	CajaMetal* cajaMetal = new CajaMetal(body);

	// Bloqueo la lista de superficies y agrego la caja.
	Lock(this->mSuperficies);
	this->superficies.push_back(cajaMetal);

	// Notifico al observador que se creo una caja de vidrio.
	if (this->observador != NULL) {
		this->observador->seAgregoCajaMetal(cajaMetal);
	}
}

void Escenario::agregarManzana(Punto2D p) {
	/* Solo puedo agregar una Manzana si la simulación no ha comenzado.
	 * Si la simulacion ya comenzo, lanzo una excepcion
	 */
	if (this->simulacionHabilitada) {
		throw AgregarObjetoException("La simulación esta corriendo, no se puede"
				" agregar Manzana.");
	}

	// Defino el cuerpo, seteo el tipo y la posicion y luego lo creo
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(p.x, p.y);
	b2Body* body = this->escenario->CreateBody(&bodyDef);

	// Creo el objeto Manzana y le paso el cuerpo de Box2D
	Manzana* manzana = new Manzana(body);

	// Bloqueo la lista de frutas y agrego la fruta.
	Lock(this->mFrutas);
	this->frutas.push_back(manzana);

	// Notifico al observador que se creo una caja de vidrio.
	if (this->observador != NULL) {
		this->observador->seAgregoManzana(manzana);
	}
}

void Escenario::agregarBanana(Punto2D p) {
	/* Solo puedo agregar una Banana si la simulación no ha comenzado.
	 * Si la simulacion ya comenzo, lanzo una excepcion
	 */
	if (this->simulacionHabilitada) {
		throw AgregarObjetoException("La simulación esta corriendo, no se puede"
				" agregar Banana.");
	}

	// Defino el cuerpo, seteo el tipo y la posicion y luego lo creo
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(p.x, p.y);
	b2Body* body = this->escenario->CreateBody(&bodyDef);

	// Creo el objeto Manzana y le paso el cuerpo de Box2D
	Banana* banana = new Banana(body);
	// Bloqueo la lista de frutas y agrego la fruta.
	Lock(this->mFrutas);
	this->frutas.push_back(banana);

	// Notifico al observador que se creo una caja de vidrio.
	if (this->observador != NULL) {
		this->observador->seAgregoBanana(banana);
	}
}

void Escenario::agregarCereza(Punto2D p) {
	/* Solo puedo agregar una Cereza si la simulación no ha comenzado.
	 * Si la simulacion ya comenzo, lanzo una excepcion
	 */
	if (this->simulacionHabilitada) {
		throw AgregarObjetoException("La simulación esta corriendo, no se puede"
				" agregar Cereza.");
	}

	// Defino el cuerpo, seteo el tipo y la posicion y luego lo creo
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(p.x, p.y);
	b2Body* body = this->escenario->CreateBody(&bodyDef);

	// Creo el objeto Manzana y le paso el cuerpo de Box2D
	Cereza* cereza = new Cereza(body);
	// Bloqueo la lista de frutas y agrego la fruta.
	Lock(this->mFrutas);
	this->frutas.push_back(cereza);

	// Notifico al observador que se creo una caja de vidrio.
	if (this->observador != NULL) {
		this->observador->seAgregoCereza(cereza);
	}
}

void Escenario::habilitarSimulacion() {
	/* Verifico si el escenario cumple con la cantidad de jugadores que se
	 * requieren.
	 */
	Lock(this->mJugadores);
	if (this->jugadores.size() != this->cantJugadores) {
		throw SimulacionException("El escenario no cumple con la cantidad de"
				"cerditos/jugadores requeridos,"
				"no se puede habilitar la simulación.");
	}

	/* Verifico que haya algun monticulo en la escena.
	 * Si no, lanzo una excepcion.
	 */
	if (this->monticulo == NULL) {
		throw SimulacionException("No hay monticulo en la escena,"
						"no se puede habilitar la simulación.");
	}

	this->simulacionHabilitada = true;
}

void Escenario::correrTick() {
	/* Verifico si la simulacion ya está habilitada.
	 * Caso contrario, lanzo una excepción.
	 */
	if (!this->simulacionHabilitada) {
		throw SimulacionException("La simulación no está habilitada.");
	}
	this->escenario->Step(TIEMPO_TICK_SEG, VELOCIDAD_ITERACIONES,
			POSICION_ITERACIONES);

	// unidades -> tiempoTick (seg), tiempoDeJuego (mseg)
	this->tiempoDeJuego += round(TIEMPO_TICK_MSEG);

	// NOTA: Si el monticulo es destruido o TODOS los cerditos han muerto
	// se ha perdido la partida.
	// Sin embargo si solo ALGUNO de los cerditos ha muerto se continua jugando.
	if (!monticulo->estaVivo()) {  // el monticulo fue destruido
		std::cout << "MONTICULO DESTRUIDO" << std::endl;
		if (this->observador != NULL) {
			this->observador->monticuloDestruido();
			this->observador->partidaPerdida();
		}
		this->finalizo = true;
	}
	if (!validarCerditosVivos()) {  // todos los cerditos estan muertos
		if (this->observador != NULL)
			this->observador->partidaPerdida();
		this->finalizo = true;
	}

	if (this->tiempoDeJuego >= this->duracionDeJuego) {  // se gano partida
		if (this->observador != NULL)
			this->observador->partidaGanada();
		this->finalizo = true;
	}

	// Elimino objetos "muertos"
	this->limpiarCuerposInvalidos();
	// Notifico al observador las nuevas posiciones de pajaros y disparos.
	this->notificarPosicionesAObservadores();
}

void Escenario::lanzarPajaroRojo(Punto2D p, Velocidad2D v) {
	/* Verifico si la simulacion ya está habilitada.
	 * Caso contrario, lanzo una excepción.
	 */
	if (!this->simulacionHabilitada) {
		throw SimulacionException("La simulación no está habilitada,"
				"no se puede lanzar un Pajaro Rojo.");
	}
	/* Defino el cuerpo, seteo el tipo de cuerpo, la posicion, la velocidad
	 * y luego lo creo.
	 */
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(p.x, p.y);
	bodyDef.linearVelocity.Set(v.x, v.y);
	// valido que b2World no este bloqueado haciendo el step()
	if (escenario->IsLocked())
		return;
	b2Body* body = this->escenario->CreateBody(&bodyDef);
	// Creo el objeto PajaroRojo y le paso el cuerpo de Box2D
	PajaroRojo* pajaro = new PajaroRojo(body);
	// Bloqueo la lista de pajaros y agrego el pajaro.
	Lock(this->mPajaros);
	this->pajaros.push_back(pajaro);
	// Notifico al observador que se lanzo un pajaro rojo
	if (this->observador != NULL)
		this->observador->seLanzoPajaroRojo(pajaro);
}

void Escenario::lanzarPajaroVerde(Punto2D p, Velocidad2D v) {
	/* Verifico si la simulacion ya está habilitada.
	 * Caso contrario, lanzo una excepción.
	 */
	if (!this->simulacionHabilitada) {
		throw SimulacionException("La simulación no está habilitada,"
				"no se puede lanzar un Pajaro Verde.");
	}
	/* Defino el cuerpo, seteo el tipo de cuerpo, la posicion, la velocidad
	 * y luego lo creo.
	 */
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(p.x, p.y);
	bodyDef.linearVelocity.Set(v.x, v.y);
	// valido que b2World no este bloqueado haciendo el step()
	if (escenario->IsLocked())
		return;
	b2Body* body = this->escenario->CreateBody(&bodyDef);
	// Creo el objeto PajaroVerde y le paso el cuerpo de Box2D
	PajaroVerde* pajaro = new PajaroVerde(body);
	// Bloqueo la lista de pajaros y agrego el pajaro.
	Lock(this->mPajaros);
	this->pajaros.push_back(pajaro);

	// Notifico al observador que se lanzo un pajaro rojo
	if (this->observador != NULL) {
		this->observador->seLanzoPajaroVerde(pajaro);
	}
}

void Escenario::lanzarPajaroAzul(Punto2D p, Velocidad2D v) {
	/* Verifico si la simulacion ya está habilitada.
	 * Caso contrario, lanzo una excepción.
	 */
	if (!this->simulacionHabilitada) {
		throw SimulacionException("La simulación no está habilitada,"
				"no se puede lanzar un Pajaro Azul.");
	}
	/* Defino el cuerpo, seteo el tipo de cuerpo, la posicion, la velocidad
	 * y luego lo creo.
	 */
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(p.x, p.y);
	bodyDef.linearVelocity.Set(v.x, v.y);
	// valido que b2World no este bloqueado haciendo el step()
	if (escenario->IsLocked())
		return;
	b2Body* body = this->escenario->CreateBody(&bodyDef);
	// Creo el objeto PajaroAzul y le paso el cuerpo de Box2D
	PajaroAzul* pajaro = new PajaroAzul(body);
	// Bloqueo la lista de pajaros y agrego el pajaro.
	Lock(this->mPajaros);
	this->pajaros.push_back(pajaro);
	// Notifico al observador que se lanzo un pajaro rojo
	if (this->observador != NULL) {
		this->observador->seLanzoPajaroAzul(pajaro);
	}
}

void Escenario::lanzarHuevoBlanco(Punto2D p, Velocidad2D v,
		unsigned int id) {
	/* Verifico si la simulacion ya está habilitada.
	 * Caso contrario, lanzo una excepción.
	 */
	if (!this->simulacionHabilitada) {
		throw SimulacionException("La simulación no está habilitada,"
				"no se puede lanzar Huevo.");
	}

	// Si el jugador es nulo, es porque no existe. Lanzo una excepcion.
	Jugador* jugador = this->getJugador(id);
	if (jugador == NULL) {
		throw NoExisteJugadorException();
	}

	/* Defino el cuerpo, seteo el tipo de cuerpo, la posicion, la velocidad
	 * y luego lo creo.
	 */
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(p.x, p.y);
	bodyDef.linearVelocity.Set(v.x, v.y);
	// valido que b2World no este bloqueado haciendo el step()
	if (escenario->IsLocked())
		return;
	b2Body* body = this->escenario->CreateBody(&bodyDef);
	// Creo el objeto HuevoBlanco y le paso el cuerpo de Box2D
	HuevoBlanco* huevo = new HuevoBlanco(body, id, jugador);
	// Bloqueo la lista de disparos y agrego el huevo.
	Lock(this->mDisparos);
	this->disparos.push_back(huevo);

	// Notifico al observador que se lanzo un huevo blanco
	if (this->observador != NULL) {
		this->observador->seLanzoHuevoBlanco(huevo);
	}
}

void Escenario::lanzarHuevosCodorniz(Punto2D p, Velocidad2D v,
		unsigned int id) {
	/* Verifico si la simulacion ya está habilitada.
	 * Caso contrario, lanzo una excepción.
	 */
	if (!this->simulacionHabilitada) {
		throw SimulacionException("La simulación no está habilitada,"
				"no se puede lanzar Huevo.");
	}

	// Si el jugador es nulo, es porque no existe. Lanzo una excepcion.
	Jugador* jugador = this->getJugador(id);
	if (jugador == NULL) {
		throw NoExisteJugadorException();
	}
	/* Defino el cuerpo, seteo el tipo de cuerpo, la posicion, la velocidad
	 * y luego lo creo.
	 */
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(p.x, p.y);
	bodyDef.linearVelocity.Set(v.x, v.y);
	// valido que b2World no este bloqueado haciendo el step()
	if (escenario->IsLocked())
		return;
	// Creo tres objeto HuevoCodorniz con distinta velocidad inicial
	// Creo el primer HuevoCodorniz
	b2Body* body1 = this->escenario->CreateBody(&bodyDef);
	HuevoCodorniz* huevo1 = new HuevoCodorniz(body1, id, jugador);
	// Creo el segundo HuevoCodorniz
	bodyDef.linearVelocity.Set(v.x, v.y * HC_OFFSET_MAX);
	b2Body* body2 = this->escenario->CreateBody(&bodyDef);
	HuevoCodorniz* huevo2 = new HuevoCodorniz(body2, id, jugador);
	// Creo el tercer HuevoCodorniz
	bodyDef.linearVelocity.Set(v.x, v.y * HC_OFFSET_MIN);
	b2Body* body3 = this->escenario->CreateBody(&bodyDef);
	HuevoCodorniz* huevo3 = new HuevoCodorniz(body3, id, jugador);
	// Bloqueo la lista de disparos y agrego los huevos.
	Lock(this->mDisparos);
	this->disparos.push_back(huevo1);
	this->disparos.push_back(huevo2);
	this->disparos.push_back(huevo3);

	// Notifico al observador que se lanzo un huevo codorniz
	if (this->observador != NULL) {
		this->observador->seLanzoHuevoCodorniz(huevo1);
		this->observador->seLanzoHuevoCodorniz(huevo2);
		this->observador->seLanzoHuevoCodorniz(huevo3);
	}
}

void Escenario::lanzarHuevoPoche(Punto2D p, Velocidad2D v,
		unsigned int id) {
	/* Verifico si la simulacion ya está habilitada.
	 * Caso contrario, lanzo una excepción.
	 */
	if (!this->simulacionHabilitada) {
		throw SimulacionException("La simulación no está habilitada,"
				"no se puede lanzar Huevo.");
	}

	// Si el jugador es nulo, es porque no existe. Lanzo una excepcion.
	Jugador* jugador = this->getJugador(id);
	if (jugador == NULL) {
		throw NoExisteJugadorException();
	}
	/* Defino el cuerpo, seteo el tipo de cuerpo, la posicion, la velocidad
	 * y luego lo creo.
	 */
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(p.x, p.y);
	bodyDef.linearVelocity.Set(v.x, v.y);
	// valido que b2World no este bloqueado haciendo el step()
	if (escenario->IsLocked())
		return;
	b2Body* body = this->escenario->CreateBody(&bodyDef);
	// Creo el objeto HuevoPoche y le paso el cuerpo de Box2D
	HuevoPoche* huevo = new HuevoPoche(body, id, jugador);
	// Bloqueo la lista de disparos y agrego el huevo.
	Lock(this->mDisparos);
	this->disparos.push_back(huevo);
	// Notifico al observador que se lanzo un huevo poche
	if (this->observador != NULL) {
		this->observador->seLanzoHuevoPoche(huevo);
	}
}

void Escenario::lanzarHuevoReloj(Punto2D p, Velocidad2D v,
		unsigned int id) {
	/* Verifico si la simulacion ya está habilitada.
	 * Caso contrario, lanzo una excepción.
	 */
	if (!this->simulacionHabilitada) {
		throw SimulacionException("La simulación no está habilitada,"
				"no se puede lanzar Huevo.");
	}

	// Si el jugador es nulo, es porque no existe. Lanzo una excepcion.
	Jugador* jugador = this->getJugador(id);
	if (jugador == NULL) {
		throw NoExisteJugadorException();
	}
	/* Defino el cuerpo, seteo el tipo de cuerpo, la posicion, la velocidad
	 * y luego lo creo.
	 */
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(p.x, p.y);
	bodyDef.linearVelocity.Set(v.x, v.y);
	// valido que b2World no este bloqueado haciendo el step()
	if (escenario->IsLocked())
		return;
	b2Body* body = this->escenario->CreateBody(&bodyDef);
	// Creo el objeto HuevoReloj y le paso el cuerpo de Box2D
	HuevoReloj* huevo = new HuevoReloj(body, id, jugador, 6000);
	// Bloqueo la lista de disparos y agrego el huevo.
	Lock(this->mDisparos);
	this->disparos.push_back(huevo);
	/* Como el HuevoReloj tiene un cierto tiempo de vida, lo agrego a la lista
	 * de ObjetosVivos.
	 */
	Lock(this->mObjetosVivos);
	this->objetosVivos.push_back(huevo);
	// Notifico al observador que se lanzo un huevo reloj
	if (this->observador != NULL) {
		this->observador->seLanzoHuevoReloj(huevo);
	}
}

bool Escenario::finalizoPartida() const {
	return this->finalizo;
}

bool Escenario::ganoPartida() const {
	// si se alcanzo el tiempo esperado se da por ganada la partida.
	return (this->tiempoDeJuego >= this->duracionDeJuego);
}

void Escenario::setTamanio(float ancho, float alto) {
	this->ancho = ancho;
	this->alto = alto;
	// Notifico al observador que se cambio el tamaño del escenario
	if (this->observador != NULL) {
		this->observador->seAjustoTamanio(this->ancho, this->alto);
	}
}

float Escenario::getAlto() const {
	return alto;
}

float Escenario::getAncho() const {
	return ancho;
}

std::string Escenario::getRutaImagenFondo() const {
	return this->rutaImagenFondo;
}

void Escenario::setRutaImagenFondo(std::string rutaArchivo) {
	this->rutaImagenFondo = rutaArchivo;
	// Notifico al observador que se cambio la imagen de fondo
	if (this->observador != NULL) {
		this->observador->seEstablecioFondo();
	}
}

std::string Escenario::getRutaImagenSuelo() const {
	return this->rutaImagenSuelo;
}

void Escenario::setRutaImagenSuelo(std::string rutaArchivo) {
	this->rutaImagenSuelo = rutaArchivo;
	// Notifico al observador que se cambio la imagen de fondo
	if (this->observador != NULL) {
		this->observador->seEstablecioSuelo();
	}
}

unsigned int Escenario::getCantidadJugadores() const {
	return this->cantJugadores;
}

Punto2D Escenario::getPosicionCatapulta(unsigned int idJugador) {
	// Si el jugador es nulo, es porque no existe. Lanzo una excepcion.
	Jugador* jugador = this->getJugador(idJugador);
	if (jugador == NULL) {
		throw NoExisteJugadorException();
	}
	return jugador->getCerdito()->getCatapulta()->getPosicion();
}

unsigned int Escenario::getIdJugadorNoConectado() {
	Lock(this->mJugadores);
	std::vector<Jugador*>::iterator it;
	for (it = jugadores.begin(); it != jugadores.end(); ++it) {
		if (!(*it)->estaConectado())
			return (*it)->getId();
	}
	return 0;
}

void Escenario::setJugadorConectado(unsigned int id) {
	Jugador* j = getJugador(id);
	j->setConectado(true);
}

void Escenario::setJugadorNoConectado(unsigned int id) {
	Jugador* j = getJugador(id);
	j->setConectado(false);
}

void Escenario::XMLGuardarAtributos(XMLNode* nodoEscenario) const {
	std::cout << "\t=== GUARDANDO ATRIBUTOS ===" << std::endl;
	// Convierto el ancho y alto en string
	std::ostringstream strAncho, strAlto;
	strAncho << this->ancho;
	strAlto << this->alto;
	nodoEscenario->SetAttribute("ancho", strAncho.str());
	nodoEscenario->SetAttribute("alto", strAlto.str());
	// Creo un nodo para la ruta de imagen del fondo y suelo y lo guardo
	XMLText* textoImagenFondo = new XMLText(this->rutaImagenFondo);
	XMLNode* nodoImagenFondo = new XMLNode("ImagenFondo");
	nodoImagenFondo->LinkEndChild(textoImagenFondo);
	XMLText* textoImagenSuelo = new XMLText(this->rutaImagenSuelo);
	XMLNode* nodoImagenSuelo = new XMLNode("ImagenSuelo");
	nodoImagenSuelo->LinkEndChild(textoImagenSuelo);
	nodoEscenario->LinkEndChild(nodoImagenFondo);
	nodoEscenario->LinkEndChild(nodoImagenSuelo);
	// Convierto la cantidad de jugadores en string
	std::ostringstream strJugadores;
	strJugadores << this->cantJugadores;
	XMLText* textoJugadores = new XMLText(strJugadores.str());
	// Creo un nodo para la cantidad de jugadores y lo guardo
	XMLNode* nodoJugadores = new XMLNode("Jugadores");
	nodoJugadores->LinkEndChild(textoJugadores);
	nodoEscenario->LinkEndChild(nodoJugadores);
}

XMLNode* Escenario::XMLGetCerditos() {
	std::cout << "\t=== GUARDANDO CERDITOS ===" << std::endl;
	// Creo el nodo de cerditos.
	XMLNode* nodo = new XMLNode("Cerditos");
	// Serializo los cerditos de los jugadores y los guardo.
	Lock(this->mJugadores);
	std::vector<Jugador*>::const_iterator it = jugadores.begin();
	while (it != jugadores.end()) {
		nodo->LinkEndChild((*it)->getCerdito()->serialize());
		it++;
	}
	return nodo;
}

XMLNode* Escenario::XMLGetSuperficies() {
	std::cout << "\t=== GUARDANDO SUPERFICIES ===" << std::endl;
	// Creo el nodo de superficies.
	XMLNode* nodo = new XMLNode("Superficies");
	// Serializo las superficies y las guardo en el nodo.
	Lock(this->mSuperficies);
	std::list<Superficie*>::const_iterator it = superficies.begin();
	while (it != superficies.end()) {
		nodo->LinkEndChild((*it)->serialize());
		it++;
	}
	return nodo;
}

XMLNode* Escenario::XMLGetFrutas() {
	std::cout << "\t=== GUARDANDO FRUTAS ===" << std::endl;
	// Creo el nodo de las frutas
	XMLNode* nodo = new XMLNode("Frutas");
	// Serializo las frutas y las guardo en el nodo.
	Lock(this->mFrutas);
	std::list<Fruta*>::const_iterator it = frutas.begin();
	while (it != frutas.end()) {
		nodo->LinkEndChild((*it)->serialize());
		it++;
	}
	return nodo;
}

XMLNode* Escenario::XMLGetPajaros() {
	std::cout << "\t=== GUARDANDO PAJAROS ===" << std::endl;
	// Creo el nodo de los pajaros
	XMLNode* nodo = new XMLNode("Pajaros");
	// Serializo los pajaros y los guardo en el nodo.
	Lock(this->mPajaros);
	std::list<Pajaro*>::const_iterator it = pajaros.begin();
	while (it != pajaros.end()) {
		nodo->LinkEndChild((*it)->serialize());
		it++;
	}
	return nodo;
}

XMLNode* Escenario::XMLGetDisparos() {
	std::cout << "\t=== GUARDANDO DISPAROS ===" << std::endl;
	// Creo el nodo de los disparos.
	XMLNode* nodo = new XMLNode("Disparos");
	// Serializo los disparos y los guardo en el nodo.
	Lock(this->mDisparos);
	std::list<Disparo*>::const_iterator it = disparos.begin();
	while (it != disparos.end()) {
		nodo->LinkEndChild((*it)->serialize());
		it++;
	}
	return nodo;
}

void Escenario::XMLCargarAtributos(const XMLNode* nodo) {
	std::cout << "\t=== CARGANDO ATRIBUTOS ===" << std::endl;
	// Verifico si contiene el atributo ancho, si no lo posee, lanzo excepcion.
	if (nodo->Attribute("ancho") == 0) {
		throw ParserException("El nodo Escenario no contiene el atributo "
				"'ancho'.");
	}
	// Verifico si contiene el atributo alto, si no lo posee, lanzo excepcion.
	if (nodo->Attribute("alto") == 0) {
		throw ParserException("El nodo Escenario no contiene el atributo "
				"'alto'.");
	}
	// Obtengo el atributo de ancho y alto
	std::istringstream atributoAncho(nodo->Attribute("ancho"));
	std::istringstream atributoAlto(nodo->Attribute("alto"));
	// Seteo la configuracion regional defaul de C++ para dichos streams.
	atributoAncho.imbue(std::locale("C"));
	atributoAlto.imbue(std::locale("C"));
	float fAncho, fAlto;
	atributoAncho >> fAncho;
	atributoAlto >> fAlto;
	this->setTamanio(fAncho, fAlto);
	std::cout << "\tAncho: " << fAncho << "\tAlto: " << fAlto << std::endl;

	// Obtengo el nodo que contiene la ruta de la imagen del fondo.
	const XMLNode* imagenFondo = nodo->FirstChildElement("ImagenFondo");
	// Si no existe el nodo ImagenFondo, lanzo una excepcion
	if (imagenFondo == 0) {
		throw ParserException("El nodo Escenario no contiene informacion sobre "
						"la imagen de fondo.");
	}
	this->setRutaImagenFondo(imagenFondo->GetText());
	std::cout << "\tRuta Imagen de fondo: " << this->rutaImagenFondo << std::endl;

	// Obtengo el nodo que contiene la ruta de la imagen del suelo.
	const XMLNode* imagenSuelo = nodo->FirstChildElement("ImagenSuelo");
	// Si no existe el nodo ImagenSuelo, lanzo una excepcion
	if (imagenSuelo == 0) {
		throw ParserException("El nodo Escenario no contiene informacion sobre "
						"la imagen de fondo.");
	}
	this->setRutaImagenSuelo(imagenSuelo->GetText());
	std::cout << "\tRuta Imagen de fondo: " << this->rutaImagenFondo << std::endl;

	// Obtengo el nodo que contiene la cantidad de jugadores que puede disponer.
	const XMLNode* jugadores = nodo->FirstChildElement("Jugadores");
	// Si no existe el nodo Jugadores, lanzo una excepcion
	if (jugadores == 0) {
		throw ParserException("El nodo Escenario no contiene informacion sobre "
						"la cantidad de jugadores que puede contener.");
	}
	this->cantJugadores = std::atoi(jugadores->GetText());
	std::cout << "\tCantidad de jugadores: " << this->cantJugadores << std::endl;
}

void Escenario::XMLCargarSuelo(const XMLNode* nodo) {
	std::cout << "\t=== CARGANDO SUELO ===" << std::endl;
}

void Escenario::XMLCargarCerditos(const XMLNode* nodo) {
	std::cout << "\t=== CARGANDO CERDITOS ===" << std::endl;
	// Obtengo el nodo que contiene la ruta de la imagen.
	const XMLNode* cerdito = nodo->FirstChildElement("Cerdito");
	// Mientras el nodo del cerdito no sea nulo, cargar el cerdito.
	while (cerdito != 0) {
		this->XMLCargarCerdito(cerdito);
		cerdito = cerdito->NextSiblingElement("Cerdito");
	}
}

void Escenario::XMLCargarCerdito(const XMLNode* nodo) {
	std::cout << "\t=== CARGANDO CERDITO ===" << std::endl;
	// Obtengo la posicion del cerdito.
	const XMLNode* posCerdito = nodo->FirstChildElement("Punto2D");
	// Si no existe el nodo Punto2D, lanzo una excepcion
	if (posCerdito == 0) {
		throw ParserException("El nodo Cerdito no contiene el nodo "
				"'Punto2D'.");
	}
	// Hidrato el punto 2D del cerdito
	Punto2D puntoCerdito(posCerdito);
	std::cout << "\tCerdito\tx= " << puntoCerdito.x << "\ty= " << puntoCerdito.y
			<< std::endl;
	// Obtengo el nodo de la catapulta.
	const XMLNode* catapulta = nodo->FirstChildElement("Catapulta");
	// Si no existe el nodo Catapulta, lanzo una excepcion
	if (catapulta == 0) {
		throw ParserException("El nodo Cerdito no contiene el nodo "
				"'Catapulta'.");
	}
	// Obtengo la posicion de la catapulta.
	const XMLNode* posCatapulta = catapulta->FirstChildElement("Punto2D");
	// Si no existe el nodo Punto2D, lanzo una excepcion
	if (posCatapulta == 0) {
		throw ParserException("El nodo Catapulta no contiene el nodo "
				"'Punto2D'.");
	}
	// Hidrato el punto 2D de la catapulta
	Punto2D puntoCatapulta(posCatapulta);
	std::cout << "\tCatapulta\tx= " << puntoCatapulta.x << "\ty= " <<
			puntoCatapulta.y << std::endl;
	// Cargo el cerdito
	unsigned int id = Escenario::generarId();
	this->agregarCerdito(puntoCerdito, puntoCatapulta, id);
}

void Escenario::XMLCargarMonticulo(const XMLNode* nodo) {
	std::cout << "\t=== CARGANDO MONTICULO ===" << std::endl;
	// Obtengo la posicion del monticulo.
	const XMLNode* punto = nodo->FirstChildElement("Punto2D");
	// Si no existe el nodo Punto2D, lanzo una excepcion
	if (punto == 0) {
		throw ParserException("El nodo Monticulo no contiene el nodo "
				"'Punto2D'.");
	}
	// Hidrato el punto 2D
	Punto2D p(punto);
	std::cout << "\tMonticulo\tx= " << p.x << "\ty= " << p.y << std::endl;
	this->agregarMonticulo(p);
}

void Escenario::XMLCargarSuperficies(const XMLNode* nodo) {
	std::cout << "\t=== CARGANDO SUPERFICIES ===" << std::endl;
	// Cargo el primer nodo de superficie
	const XMLNode* supNode = nodo->FirstChildElement();
	// Mientras el nodo de superficie no es nulo, la hidrato y agrego
	while (supNode != 0) {
		// Obtengo el nodo de Punto2D de la superficie
		const XMLNode* puntoNode = supNode->FirstChildElement("Punto2D");
		// Si el nodo del punto no es nulo, cargo la superficie
		if (puntoNode != 0) {
			// Hidrato el punto 2D
			Punto2D p(puntoNode);
			// Obtengo el nombre del nodo de superficie
			std::string supName = supNode->ValueStr();
			switch (mapSuperficies[supName]) {
			case supCajaVidrio:
				std::cout << "\tCajaVidrio\tx= " << p.x << "\ty= " << p.y <<
				std::endl;
				this->agregarCajaVidrio(p);
				break;
			case supCajaMadera:
				std::cout << "\tCajaMadera\tx= " << p.x << "\ty= " << p.y <<
				std::endl;
				this->agregarCajaMadera(p);
				break;
			case supCajaMetal:
				std::cout << "\tCajaMetal\tx= " << p.x << "\ty= " << p.y <<
				std::endl;
				this->agregarCajaMetal(p);
				break;
			default:
				std::cout << "\tNodo de Superficie no válido" << std::endl;
				break;
			}  // Fin switch
		}  // Fin if nodo punto no nulo
		// Obtengo el siguiente nodo de superficie
		supNode = supNode->NextSiblingElement();
	}  // Fin while
}

void Escenario::XMLCargarFrutas(const XMLNode* nodo) {
	std::cout << "\t=== CARGANDO FRUTAS ===" << std::endl;
	// Cargo el primer nodo de fruta
	const XMLNode* fruNode = nodo->FirstChildElement();
	// Mientras el nodo de fruta no es nulo, la hidrato y agrego
	while (fruNode != 0) {
		// Obtengo el nodo de Punto2D de la fruta
		const XMLNode* puntoNode = fruNode->FirstChildElement("Punto2D");
		// Si el nodo del punto no es nulo, cargo la fruta
		if (puntoNode != 0) {
			// Hidrato el punto 2D
			Punto2D p(puntoNode);
			// Obtengo el nombre del nodo de fruta
			std::string fruName = fruNode->ValueStr();
			switch (mapFrutas[fruName]) {
			case fruManzana:
				std::cout << "\tManzana\tx= " << p.x << "\ty= " << p.y <<
				std::endl;
				this->agregarManzana(p);
				break;
			case fruBanana:
				std::cout << "\tBanana\tx= " << p.x << "\ty= " << p.y <<
				std::endl;
				this->agregarBanana(p);
				break;
			case fruCereza:
				std::cout << "\tCereza\tx= " << p.x << "\ty= " << p.y <<
				std::endl;
				this->agregarCereza(p);
				break;
			default:
				std::cout << "\tNodo de Fruta no válido" << std::endl;
				break;
			}  // Fin switch
		}  // Fin if nodo punto no nulo
		// Obtengo el siguiente nodo de fruta
		fruNode = fruNode->NextSiblingElement();
	}  // Fin while
}

void Escenario::XMLCargarPajaros(const XMLNode* nodo) {
	std::cout << "\t=== CARGANDO PAJAROS ===" << std::endl;
	// Cargo el primer nodo de pajaro
	const XMLNode* pajNode = nodo->FirstChildElement();
	// Mientras el nodo de pajaro no es nulo, la hidrato y agrego
	while (pajNode != 0) {
		// Obtengo el nodo de Punto2D y Velocidad2D del pajaro
		const XMLNode* posNode = pajNode->FirstChildElement("Punto2D");
		const XMLNode* velNode = pajNode->FirstChildElement("Velocidad2D");
		// Si los nodos de pocision y velocidad no son nulos, cargo el pajaro.
		if ((posNode != 0) && (velNode != 0)) {
			// Hidrato el punto 2D y la velocidad 2D
			Punto2D p(posNode);
			Velocidad2D v(velNode);
			// Obtengo el nombre del nodo de pajaro
			std::string pajName = pajNode->ValueStr();
			switch (mapPajaros[pajName]) {
			case pajPajaroRojo:
				std::cout << "\tPajaroRojo\tPosicion: x= " << p.x << "\ty= " <<
				p.y << std::endl;
				std::cout << "\t\t\tVelocidad: x= " << v.x << "\ty= " << v.y <<
						std::endl;
				this->lanzarPajaroRojo(p, v);
				break;
			case pajPajaroVerde:
				std::cout << "\tPajaroVerde\tPosicion: x= " << p.x << "\ty= " <<
				p.y << std::endl;
				std::cout << "\t\t\tVelocidad: x= " << v.x << "\ty= " << v.y <<
						std::endl;
				this->lanzarPajaroVerde(p, v);
				break;
			case pajPajaroAzul:
				std::cout << "\tPajaroAzul\tPosicion: x= " << p.x << "\ty= " <<
				p.y << std::endl;
				std::cout << "\t\t\tVelocidad: x= " << v.x << "\ty= " << v.y <<
						std::endl;
				this->lanzarPajaroAzul(p, v);
				break;
			default:
				std::cout << "\tNodo de Pajaro no válido" << std::endl;
				break;
			}  // Fin switch
		}  // Fin if nodos punto y velocidad no nulos
		// Obtengo el siguiente nodo de pajaro
		pajNode = pajNode->NextSiblingElement();
	}  // Fin while
}

void Escenario::XMLCargarDisparos(const XMLNode* nodo) {
	std::cout << "\t=== CARGANDO DISPAROS ===" << std::endl;
	// Cargo el primer nodo de disparo
	const XMLNode* disNode = nodo->FirstChildElement();
	// Mientras el nodo de disparo no es nulo, lo hidrato y agrego
	while (disNode != 0) {
		// Obtengo el ID del jugador.
		int jugadorID = 0;
		const char* atributo = disNode->Attribute("jugadorID", &jugadorID);
		// Obtengo el nodo de Punto2D y Velocidad2D del disparo
		const XMLNode* posNode = disNode->FirstChildElement("Punto2D");
		const XMLNode* velNode = disNode->FirstChildElement("Velocidad2D");
		/* Si el atributo de id, los nodos de pocision y velocidad no son nulos,
		 * cargo el disparo.
		 */
		if ((posNode != 0) && (velNode != 0) && (atributo != 0)) {
			// Hidrato el punto 2D y la velocidad 2D
			Punto2D p(posNode);
			Velocidad2D v(velNode);
			// Obtengo el jugador correspondiente.
			// Si el jugador es nulo, es porque no existe. Lanzo una excepcion.
			Jugador* jugador = this->getJugador(jugadorID);
			if (jugador == NULL) {
				throw ParserException("Informacion de jugador malformada.");
			}
			// Obtengo el nombre del nodo de disparo
			std::string disName = disNode->ValueStr();
			switch (mapDisparos[disName]) {
			case disHuevoBlanco:
				std::cout << "\tHuevoBlanco\tJugador: " << jugadorID << std::endl;
				std::cout << "\t\tPosicion: x= " << p.x << "\ty= " << p.y << std::endl;
				std::cout << "\t\tVelocidad: x= " << v.x << "\ty= " << v.y << std::endl;
				this->lanzarHuevoBlanco(p, v, jugadorID);
				break;
			case disHuevoCodorniz:
				std::cout << "\tHuevoCodorniz\tJugador: " << jugadorID << std::endl;
				std::cout << "\t\tPosicion: x= " << p.x << "\ty= " << p.y << std::endl;
				std::cout << "\t\tVelocidad: x= " << v.x << "\ty= " << v.y << std::endl;
				this->lanzarHuevosCodorniz(p, v, jugadorID);
				break;
			case disHuevoPoche:
				std::cout << "\tHuevoPoche\tJugador: " << jugadorID << std::endl;
				std::cout << "\t\tPosicion: x= " << p.x << "\ty= " << p.y << std::endl;
				std::cout << "\t\tVelocidad: x= " << v.x << "\ty= " << v.y << std::endl;
				this->lanzarHuevoPoche(p, v, jugadorID);
				break;
			case disHuevoReloj:
				std::cout << "\tHuevoReloj\tJugador: " << jugadorID << std::endl;
				std::cout << "\t\tPosicion: x= " << p.x << "\ty= " << p.y << std::endl;
				std::cout << "\t\tVelocidad: x= " << v.x << "\ty= " << v.y << std::endl;
				this->lanzarHuevoReloj(p, v, jugadorID);
				break;
			default:
				std::cout << "\tNodo de Disparo no válido" << std::endl;
				break;
			}  // Fin switch
		}  // Fin if nodos punto y velocidad no nulos
		// Obtengo el siguiente nodo de disparo
		disNode = disNode->NextSiblingElement();
	}  // Fin while
}

Jugador* Escenario::getJugador(unsigned int id) {
	Lock(this->mJugadores);
	std::vector<Jugador*>::iterator it;
	for (it = jugadores.begin(); it != jugadores.end(); ++it) {
		if ((*it)->getId() == id)
			return (*it);
	}
	return NULL;
}

bool Escenario::jugadoresCompletos() {
	std::vector<Jugador*>::iterator it;
	for (it = jugadores.begin(); it != jugadores.end(); ++it) {
		if (!(*it)->estaConectado())
			return false;
	}
	return true;
}

unsigned int Escenario::proximoId = 0;

unsigned int Escenario::generarId() {
	++Escenario::proximoId;
	return Escenario::proximoId;
}

bool Escenario::validarCerditosVivos() {
	bool resultado = false;
	Lock(this->mJugadores);
	std::vector<Jugador*>::iterator it;
	for (it = jugadores.begin(); it != jugadores.end(); ++it) {
		if ((*it)->perdio()) {
			Cerdito* c = (*it)->getCerdito();
			if (c->getBody() != NULL) {  // valido que no se haya eliminado antes.
				// elimina cerdito de mundo fisico (Box2D).
				escenario->DestroyBody(c->getBody());
				c->eliminarBody();
			}
		} else {  // hay cerdito vivo.
			resultado = true;
		}
	}
	return resultado;
}

void Escenario::limpiarCuerposInvalidos() {
	// NOTA: precaucion al eliminar cuando se itera.
	Lock(this->mSuperficies);
	std::list<Superficie*>::iterator itSu = superficies.begin();
	while (itSu != superficies.end()) {
		if (!(*itSu)->estaVivo()) {
			escenario->DestroyBody((*itSu)->getBody());
			delete (*itSu);
			itSu = superficies.erase(itSu);
		} else {
			++itSu;
		}
	}
	Lock(this->mFrutas);
	std::list<Fruta*>::iterator itFr = frutas.begin();
	while (itFr != frutas.end()) {
		if (!(*itFr)->estaVivo()) {
			escenario->DestroyBody((*itFr)->getBody());
			delete (*itFr);
			itFr = frutas.erase(itFr);
		} else {
			++itFr;
		}
	}
	Lock(this->mPajaros);
	std::list<Pajaro*>::iterator itPa = pajaros.begin();
	while (itPa != pajaros.end()) {
		if (!(*itPa)->estaVivo()) {
			escenario->DestroyBody((*itPa)->getBody());
			delete (*itPa);
			itPa = pajaros.erase(itPa);
		} else {
			++itPa;
		}
	}
	Lock(this->mDisparos);
	std::list<Disparo*>::iterator itDi = disparos.begin();
	while (itDi != disparos.end()) {
		if (!(*itDi)->estaVivo()) {
			escenario->DestroyBody((*itDi)->getBody());
			/* FIXME Verificar si el disparo es un huevo reloj.
			 * En caso correcto, eliminarlo de la lista de ObjetosVivos
			 */
			delete (*itDi);
			itDi = disparos.erase(itDi);
		} else {
			++itDi;
		}
	}
}

void Escenario::notificarPosicionesAObservadores() {
	Lock(this->mPajaros);
	std::list<Pajaro*>::iterator itPaj;
	for(itPaj = pajaros.begin(); itPaj != pajaros.end(); ++itPaj) {
		(*itPaj)->notificarPosicionAObservador();
	}
	Lock(this->mDisparos);
	std::list<Disparo*>::iterator itDis;
	for(itDis = disparos.begin(); itDis != disparos.end(); ++itDis) {
		(*itDis)->notificarPosicionAObservador();
	}
}

Escenario::SuperficiesMap Escenario::inicializarMapaSuperficies() {
	SuperficiesMap supMap;
	supMap["CajaVidrio"] = supCajaVidrio;
	supMap["CajaMadera"] = supCajaMadera;
	supMap["CajaMetal"] = supCajaMetal;
	return supMap;
}

Escenario::SuperficiesMap Escenario::mapSuperficies(Escenario::
		inicializarMapaSuperficies());

Escenario::FrutasMap Escenario::inicializarMapaFrutas() {
	FrutasMap fruMap;
	fruMap["Manzana"] = fruManzana;
	fruMap["Banana"] = fruBanana;
	fruMap["Cereza"] = fruCereza;
	return fruMap;
}

Escenario::FrutasMap Escenario::mapFrutas(Escenario::inicializarMapaFrutas());

Escenario::PajarosMap Escenario::inicializarMapaPajaros() {
	PajarosMap pajMap;
	pajMap["PajaroRojo"] = pajPajaroRojo;
	pajMap["PajaroVerde"] = pajPajaroVerde;
	pajMap["PajaroAzul"] = pajPajaroAzul;
	return pajMap;
}

Escenario::PajarosMap Escenario::mapPajaros(Escenario::
		inicializarMapaPajaros());

Escenario::DisparosMap Escenario::inicializarMapaDisparos() {
	DisparosMap disMap;
	disMap["HuevoBlanco"] = disHuevoBlanco;
	disMap["HuevoCodorniz"] = disHuevoCodorniz;
	disMap["HuevoPoche"] = disHuevoPoche;
	disMap["HuevoReloj"] = disHuevoReloj;
	return disMap;
}

Escenario::DisparosMap Escenario::mapDisparos(Escenario::
		inicializarMapaDisparos());
