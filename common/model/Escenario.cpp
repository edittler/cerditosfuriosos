// C++ Library Includes.
#include <cstdlib>  // Para usar la funcion 'atof'
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

Escenario::Escenario(unsigned int cantidadJugadores) {
	// Inicializo los atributos de dimensiones.
	this->ancho = 0;
	this->alto = 0;
	// Inicializo la cantidad de jugadores que va a tener el escenario
	this->cantJugadores = cantidadJugadores;
	// Defino el tiempo de duracion de 1 tick
	this->tiempoTick = 1.0f / 50.0f;  // 20 milisegundos
	// Defino que la simulacion no comenzo
	this->simulacionHabilitada = false;
	// Establezco el observadro, suelo y monticulo como NULL.
	this->observador = NULL;
	this->suelo = NULL;
	this->monticulo = NULL;

	// Creo el mundo
	b2Vec2 gravity(GRAVEDAD_X, GRAVEDAD_Y);  // Vector que indica la gravedad
	this->escenario = new b2World(gravity);

	/* FIXME por ahora se crea un suelo por defecto aqui, mas adelante deberia
	 * llamarse al metodo directamente desde el disenador.
	 */
	std::list<Punto2D*> p;
	agregarSuelo(p);

	// Agrego el ContactListener
	this->colisionador = new Colisionador();
	this->escenario->SetContactListener(this->colisionador);

	this->finalizo = false;
}

Escenario::~Escenario() {
	// Libero la memoria del escenario de Box2D
	delete this->escenario;
	// Libero la memoria del colisionador
	delete this->colisionador;
	// Libero la memoria de los jugadores
	std::vector<Jugador*>::iterator itJ;
	for(itJ = this->jugadores.begin(); itJ != this->jugadores.end(); ++itJ) {
		delete (*itJ);
	}
	// Libero la memoria de los objetos
	std::list<Superficie*>::iterator itSup;
	for(itSup = superficies.begin(); itSup != superficies.end(); ++itSup) {
		delete (*itSup);
	}
	std::list<Fruta*>::iterator itFru;
	for(itFru = frutas.begin(); itFru != frutas.end(); ++itFru) {
		delete (*itFru);
	}
	std::list<Pajaro*>::iterator itPaj;
	for(itPaj = pajaros.begin(); itPaj != pajaros.end(); ++itPaj) {
		delete (*itPaj);
	}
	std::list<Disparo*>::iterator itDis;
	for(itDis = disparos.begin(); itDis != disparos.end(); ++itDis) {
		delete (*itDis);
	}
	//Libero la memoria del monticulo
	if (this->monticulo != NULL)
		delete this->monticulo;
	// Libero la memoria del Suelo
	if (this->suelo != NULL)
		delete this->suelo;
}

XMLNode* Escenario::serialize() {
	return 0;
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
//	this->habilitarSimulacion();
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
	/* TODO Hay que validad que haya un único suelo, caso contrario hay que
	 * lanzar una excepcion.
	 */

	// Defino el cuerpo del suelo.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	// Creo el cuerpo del suelo.
	b2Body* groundBody = this->escenario->CreateBody(&groundBodyDef);

	Suelo* suelo = new Suelo(groundBody);
	this->suelo = suelo;
}

void Escenario::agregarCerdito(Punto2D posCerdito, Punto2D posCatapulta) {
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
	// El cerdito está asociado a un jugador. Creo dicho jugador y le paso el cerdito.
	Jugador* jugador = new Jugador(cerdito);
	// Agrego el jugador en la lista de jugadores.
	this->jugadores.push_back(jugador);
	/* No agrego al cerdito en la lista de objetos porque lo administra y
	 * liberará su memoria el jugador asociado
	 */
	// Notifico al observador se que agrego un cerdito
	if (this->observador != NULL) {
		this->observador->seAgregoCerdito(cerdito);
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
	this->superficies.push_back(cajaVidrio);

	// Notifico al observador que se creo una caja de vidrio.
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
	if (this->jugadores.size() != this->cantJugadores) {
		throw SimulacionException("El escenario no cumple con la cantidad de"
				"cerditos/jugadores requeridos,"
				"no se puede habilitar la simulación.");
	}

	/* Verifico que haya algun monticulo en la escena. Si no, lanzo una excepcion. */
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
	this->escenario->Step(this->tiempoTick, VELOCIDAD_ITERACIONES, POSICION_ITERACIONES);
	// Imprimo las posiciones de los objetos. TODO Provisorio.
//	this->imprimirPosiciones();

	// NOTA: Si el monticulo es destruido o todos los cerditos han muerto
	// se ha perdido la partida.
	// Sin embargo si solo alguno de los cerditos ha muerto se continua jugando.

	if (!monticulo->estaVivo()) {  // el monticulo fue destruido
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
	this->pajaros.push_back(pajaro);

	// Notifico al observador que se lanzo un pajaro rojo
	if (this->observador != NULL) {
		this->observador->seLanzoPajaroAzul(pajaro);
	}
}

void Escenario::lanzarHuevo(Punto2D posInicial, Velocidad2D velInicial, unsigned int j) {
	/* Verifico si la simulacion ya está habilitada.
	 * Caso contrario, lanzo una excepción.
	 */
	if (!this->simulacionHabilitada) {
		throw SimulacionException("La simulación no está habilitada,"
				"no se puede lanzar Huevo.");
	}

	// Si el jugador es nulo, es porque no existe. Lanzo una excepcion.
	Jugador* jugador = this->getJugador(j);
	if (jugador == NULL) {
		throw NoExisteJugadorException();
	}

	int random = rand() % 100;

	std::cout<< "\t random: " << random << std::endl;

	if (random < HB_PROBABILIDAD) {
		this->lanzarHuevoBlanco(posInicial, velInicial, jugador);
	} else if (random - HB_PROBABILIDAD  < HC_PROBABILIDAD) {
		this->lanzarHuevosCodorniz(posInicial, velInicial, jugador);
	} else if (random - HB_PROBABILIDAD - HC_PROBABILIDAD < HP_PROBABILIDAD) {
		this->lanzarHuevoPoche(posInicial, velInicial, jugador);
	} else if (random - HB_PROBABILIDAD - HC_PROBABILIDAD - HP_PROBABILIDAD
			< HR_PROBABILIDAD) {
		this->lanzarHuevoReloj(posInicial, velInicial, jugador);
	}
}

void Escenario::lanzarHuevoBlanco(Punto2D p, Velocidad2D v, Jugador* jugador) {
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
	HuevoBlanco* huevo = new HuevoBlanco(body, jugador);
	this->disparos.push_back(huevo);

	// Notifico al observador que se lanzo un huevo blanco
	if (this->observador != NULL) {
		this->observador->seLanzoHuevoBlanco(huevo);
	}
}

void Escenario::lanzarHuevosCodorniz(Punto2D p, Velocidad2D v, Jugador* jugador) {
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
	b2Body* body1 = this->escenario->CreateBody(&bodyDef);
	HuevoCodorniz* huevo1 = new HuevoCodorniz(body1, jugador);


	bodyDef.linearVelocity.Set(v.x, v.y * HC_OFFSET_MAX);
	b2Body* body2 = this->escenario->CreateBody(&bodyDef);
	HuevoCodorniz* huevo2 = new HuevoCodorniz(body2, jugador);

	bodyDef.linearVelocity.Set(v.x, v.y * HC_OFFSET_MIN);
	b2Body* body3 = this->escenario->CreateBody(&bodyDef);
	HuevoCodorniz* huevo3 = new HuevoCodorniz(body3, jugador);

	// Agrego disparos
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

void Escenario::lanzarHuevoPoche(Punto2D p, Velocidad2D v, Jugador* jugador) {
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
	HuevoPoche* huevo = new HuevoPoche(body, jugador);
	this->disparos.push_back(huevo);

	// Notifico al observador que se lanzo un huevo poche
	if (this->observador != NULL) {
		this->observador->seLanzoHuevoPoche(huevo);
	}
}

void Escenario::lanzarHuevoReloj(Punto2D p, Velocidad2D v, Jugador* jugador) {
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
	HuevoReloj* huevo = new HuevoReloj(body, jugador);
	this->disparos.push_back(huevo);

	// Notifico al observador que se lanzo un huevo reloj
	if (this->observador != NULL) {
		this->observador->seLanzoHuevoReloj(huevo);
	}
}

bool Escenario::finalizoPartida() {
	return this->finalizo;
}

unsigned int Escenario::getAlto() const {
	return alto;
}

void Escenario::setAlto(unsigned int alto) {
	this->alto = alto;
}

unsigned int Escenario::getAncho() const {
	return ancho;
}

void Escenario::setAncho(unsigned int ancho) {
	this->ancho = ancho;
}

std::string Escenario::getRutaImagenFondo() const {
	return this->rutaImagenFondo;
}

void Escenario::setRutaImagenFondo(std::string rutaArchivo) {
	this->rutaImagenFondo = rutaArchivo;
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
	std::string atributoAncho = nodo->Attribute("ancho");
	std::string atributoAlto = nodo->Attribute("alto");
	this->ancho = std::atof(atributoAncho.c_str());
	this->alto = std::atof(atributoAlto.c_str());
	std::cout << "\tAncho: " << ancho << "\tAlto: " << alto << std::endl;  // TODO Provisorio

	// Obtengo el nodo que contiene la ruta de la imagen.
	const XMLNode* imagen = nodo->FirstChildElement("Imagen");
	// Si no existe el nodo Imagen, lanzo una excepcion
	if (imagen == 0) {
		throw ParserException("El nodo Escenario no contiene informacion sobre "
						"la imagen de fondo.");
	}
	this->rutaImagenFondo = imagen->GetText();
	std::cout << "\tRuta Imagen de fondo: " << this->rutaImagenFondo << std::endl;
	// Obtengo el nodo que contiene la cantidad de jugadores que puede disponer.
	const XMLNode* jugadores = nodo->FirstChildElement("Jugadores");
	// Si no existe el nodo Jugadores, lanzo una excepcion
	if (imagen == 0) {
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
	std::cout << "Cerdito: \t x= " << puntoCerdito.x << "\ty= " << puntoCerdito.y << std::endl;
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
	std::cout << "Catapulta: \t x= " << puntoCatapulta.x << "\ty= " << puntoCatapulta.y << std::endl;
	// Cargo el cerdito
	this->agregarCerdito(puntoCerdito, puntoCatapulta);
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
	std::cout << "Monticulo: \t x= " << p.x << "\ty= " << p.y << std::endl;
	this->agregarMonticulo(p);
}

void Escenario::XMLCargarSuperficies(const XMLNode* nodo) {
	std::cout << "\t=== CARGANDO SUPERFICIES ===" << std::endl;
}

void Escenario::XMLCargarFrutas(const XMLNode* nodo) {
	std::cout << "\t=== CARGANDO FRUTAS ===" << std::endl;
}

void Escenario::XMLCargarPajaros(const XMLNode* nodo) {
	std::cout << "\t=== CARGANDO PAJAROS ===" << std::endl;
}

void Escenario::XMLCargarDisparos(const XMLNode* nodo) {
	std::cout << "\t=== CARGANDO DISPAROS ===" << std::endl;
}

Jugador* Escenario::getJugador(unsigned int indice) {
	Jugador* jugador;
	try {
		jugador = this->jugadores.at(indice);
	} catch (std::out_of_range& e) {  // indice incorrecto
		return NULL;
	}
	return jugador;
}

bool Escenario::validarCerditosVivos() {
	bool resultado = false;

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
	//NOTA: precaucion al eliminar cuando se itera.

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

	std::list<Disparo*>::iterator itDi = disparos.begin();
	while (itDi != disparos.end()) {
		if (!(*itDi)->estaVivo()) {
			escenario->DestroyBody((*itDi)->getBody());
			delete (*itDi);
			itDi = disparos.erase(itDi);
		} else {
			++itDi;
		}
	}

}

void Escenario::notificarPosicionesAObservadores() {
	std::list<Pajaro*>::iterator itPaj;
	for(itPaj = pajaros.begin(); itPaj != pajaros.end(); ++itPaj) {
		(*itPaj)->notificarPosicionAObservador();
	}
	std::list<Disparo*>::iterator itDis;
	for(itDis = disparos.begin(); itDis != disparos.end(); ++itDis) {
		(*itDis)->notificarPosicionAObservador();
	}
}

void Escenario::imprimirPosiciones() {
	this->monticulo->printPosition();

	// Imprimo las pocisiones de los cuerpos del escenario
	std::list<Superficie*>::iterator itSup;
	for(itSup = superficies.begin(); itSup != superficies.end(); ++itSup) {
		(*itSup)->printPosition();
	}
	std::list<Fruta*>::iterator itFru;
	for(itFru = frutas.begin(); itFru != frutas.end(); ++itFru) {
		(*itFru)->printPosition();
	}
	std::list<Pajaro*>::iterator itPaj;
	for(itPaj = pajaros.begin(); itPaj != pajaros.end(); ++itPaj) {
		(*itPaj)->printPosition();
	}
	std::list<Disparo*>::iterator itDis;
	for(itDis = disparos.begin(); itDis != disparos.end(); ++itDis) {
		(*itDis)->printPosition();
	}
}
