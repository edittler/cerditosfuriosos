// Project Includes
#include "Escenario.h"
#include "Colisionador.h"
#include "Jugador.h"
#include "Constantes.h"
#include "Suelo.h"

// Superficies Includes.
#include "CajaMadera.h"

// Pajaros Include.
#include "PajaroRojo.h"

// Disparos Include.
#include "HuevoBlanco.h"

// Other Objects Includes.
#include "Catapulta.h"
#include "Cerdito.h"

// Exceptions Includes.
#include "exceptions/AgregarObjetoException.h"
#include "exceptions/SimulacionException.h"
#include "exceptions/NoExisteJugadorException.h"

Escenario::Escenario() {
	// Defino el tiempo de duracion de 1 tick
	this->tiempoTick = 1.0f / 50.0f;  // 20 milisegundos
	// Defino que la simulacion no comenzo
	this->simulacionHabilitada = false;
	// Establezco el monticulo como NULL
//	this->monticulo = NULL;

	// Creo el mundo
	b2Vec2 gravity(0.0f, -10.0f);  // Vector que indica la gravedad
	this->escenario = new b2World(gravity);

	// FIXME por ahora se crea un suelo por defecto aqui, mas adelante deberia llamarse al metodo
	// directamente desde el disenador
	std::list<Punto2D*> p;
	agregarSuelo(p);

	// Agrego el ContactListener
	this->colisionador = new Colisionador();
	this->escenario->SetContactListener(this->colisionador);
}

Escenario::~Escenario() {
	// Libero la memoria del escenario de Box2D
	delete this->escenario;
	// Libero la memoria del colisionador
	delete this->colisionador;
	// Libero la memoria de los jugadores
	std::list<Jugador*>::iterator itJ;
	for(itJ = this->jugadores.begin(); itJ != this->jugadores.end(); ++itJ) {
		delete (*itJ);
	}
	// Libero la memoria de los objetos
	std::list<CuerpoAbstracto*>::iterator it;
	for(it = this->objetos.begin(); it != this->objetos.end(); ++it) {
		delete (*it);
	}
}

XMLNode Escenario::serialize() {
	return 0;
}

void Escenario::hydrate(const XMLNode& nodo) {

}

void Escenario::agregarSuelo(std::list<Punto2D*>& puntos) {
	// TODO implementar, el codigo siguiente no utilza @puntos para
	// hacer la interpolacion de puntos. Solo crea un suelo rectangular

	// Defino el cuerpo del suelo.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	// Creo el cuerpo del suelo.
	b2Body* groundBody = this->escenario->CreateBody(&groundBodyDef);

	CuerpoAbstracto* suelo = new Suelo(groundBody);
	this->objetos.push_back(suelo);
}

void Escenario::agregarCerdito(Punto2D posCerdito, Punto2D posCatapulta) {
	/* Solo puedo agregar un cerdito y su catapulta si la simulación no ha
	 * comenzado. Si la simulacion ya comenzo, lanzo una excepcion
	 */
	if (this->simulacionHabilitada) {
		throw AgregarObjetoException("La simulación esta corriendo, no se puede"
				" agregar Cerdito.");
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
	/* El cerdito está asociado a un jugador. Creo dicho jugador y le paso el
	 * cerdito.
	 */
	Jugador* jugador = new Jugador(cerdito);
	// Agrego el jugador en la lista de jugadores.
	this->jugadores.push_back(jugador);
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
	CuerpoAbstracto* cajaMadera = new CajaMadera(body);
	this->objetos.push_back(cajaMadera);
}

void Escenario::habilitarSimulacion() {
	/* Verifico si hay al menos un jugador. Es decir, si la lista de jugadores
	 * no está vacia. Si no, lanzo una excepción.
	 */
	if (this->jugadores.empty()) {
		throw SimulacionException("No hay jugadores/cerditos en la escena,"
				"no se puede habilitar la simulación.");
	}
	/* TODO Verifico si la escena contiene el unico monticulo de huevos.
	 * Si no, lanzo una excepción.
	 */
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
	std::list<CuerpoAbstracto*>::iterator it;
	it = objetos.begin();
	for(it = this->objetos.begin(); it != this->objetos.end(); ++it) {
		(*it)->printPosition();
	}

	// Elimino objetos "muertos"
	limpiarCuerposMuertos();
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
	b2Body* body = this->escenario->CreateBody(&bodyDef);
	// Creo el objeto PajaroRojo y le paso el cuerpo de Box2D
	CuerpoAbstracto* pajaroRojo = new PajaroRojo(body);
	this->objetos.push_back(pajaroRojo);
}

void Escenario::lanzarHuevoBlanco(Punto2D p, Velocidad2D v, unsigned int j) {
	/* Verifico si la simulacion ya está habilitada.
	 * Caso contrario, lanzo una excepción.
	 */
	if (!this->simulacionHabilitada) {
		throw SimulacionException("La simulación no está habilitada,"
				"no se puede lanzar Huevo Blanco.");
	}
	Jugador* jugador = this->getJugador(j);
	// Si el jugador es nulo, es porque no existe. Lanzo una excepcion.
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
	b2Body* body = this->escenario->CreateBody(&bodyDef);
	// Creo el objeto HuevoBlanco y le paso el cuerpo de Box2D
	CuerpoAbstracto* huevoBlanco = new HuevoBlanco(body, jugador);
	this->objetos.push_back(huevoBlanco);
}

Jugador* Escenario::getJugador(unsigned int indice) {
	// El indice comienza a partir del valor 1. Si el indice es 0, retorno NULL.
	if (indice == 0) {
		return NULL;
	} else {
		// Si el indice es 1, retorno el primer elemento de la lista.
		if (indice == 1) {
			return this->jugadores.front();
		} else {
			// Busco el jugador y lo retorno
			Jugador* jugador = NULL;
			unsigned int i = 1;
			std::list<Jugador*>::iterator it = this->jugadores.begin();
			while ((i <= indice) && (it != this->jugadores.end())) {
				if (i == indice) {
					jugador = (*it);
				}
				i++;
				it++;
			}
			return jugador;
		}  // Fin else indice == 1.
	}  // Fin else indice == 0.
}

void Escenario::limpiarCuerposMuertos() {
	b2Body* node = this->escenario->GetBodyList();
	while (node != NULL) {
		CuerpoAbstracto* cuerpo = (CuerpoAbstracto*)node->GetUserData();
		if (!cuerpo->estaVivo()) {
			std::cout << "\nElimino objeto muerto: ";  // FIXME borrar
			cuerpo->printPosition();  // FIXME borrar
			objetos.remove(cuerpo);
			this->escenario->DestroyBody(node);
		}
		node = node->GetNext();
	}
}
