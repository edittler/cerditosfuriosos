// Project Includes
#include "Escenario.h"
#include "Colisionador.h"
#include "Jugador.h"
#include "Constantes.h"
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
#include "exceptions/AgregarObjetoException.h"
#include "exceptions/SimulacionException.h"
#include "exceptions/NoExisteJugadorException.h"

Escenario::Escenario() {
	// Defino el tiempo de duracion de 1 tick
	this->tiempoTick = 1.0f / 50.0f;  // 20 milisegundos
	// Defino que la simulacion no comenzo
	this->simulacionHabilitada = false;
	// Establezco el observadro, suelo y monticulo como NULL.
	this->observador = NULL;
	this->suelo = NULL;
	this->monticulo = NULL;

	// Creo el mundo
	b2Vec2 gravity(0.0f, -10.0f);  // Vector que indica la gravedad
	this->escenario = new b2World(gravity);

	/* FIXME por ahora se crea un suelo por defecto aqui, mas adelante deberia
	 * llamarse al metodo directamente desde el disenador.
	 */
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

XMLNode Escenario::serialize() {
	return 0;
}

void Escenario::hydrate(const XMLNode& nodo) {

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
	/* TODO Implementar de manera similar a CajaMadera
	 *
	 */
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
	/* TODO Implementar de manera similar a CajaMadera
	 *
	 */
}

void Escenario::agregarManzana(Punto2D p) {
	/* TODO Implementar de manera similar a cualquiera de las superficies
	 *
	 */
}

void Escenario::agregarBanana(Punto2D p) {
	/* TODO Implementar de manera similar a cualquiera de las superficies
	 *
	 */
}

void Escenario::agregarCereza(Punto2D p) {
	/* TODO Implementar de manera similar a cualquiera de las superficies
	 *
	 */
}

void Escenario::habilitarSimulacion() {
	/* Verifico si hay al menos un jugador. Es decir, si la lista de jugadores
	 * no está vacia. Si no, lanzo una excepción.
	 */
	if (this->jugadores.empty()) {
		throw SimulacionException("No hay jugadores/cerditos en la escena,"
				"no se puede habilitar la simulación.");
	}

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
	this->imprimirPosiciones();
	// Elimino objetos "muertos"
	this->limpiarCuerposMuertos();
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
	b2Body* body = this->escenario->CreateBody(&bodyDef);
	// Creo el objeto PajaroRojo y le paso el cuerpo de Box2D
	PajaroRojo* pajaro = new PajaroRojo(body);
	this->pajaros.push_back(pajaro);
	// Notifico al observador que se lanzo un pajaro rojo
	if (this->observador != NULL)
		this->observador->seLanzoPajaroRojo(pajaro);
}

void Escenario::lanzarPajaroVerde(Punto2D p, Velocidad2D v) {
	/* TODO Implementar de manera similar a PajaroRojo
	 *
	 */
}

void Escenario::lanzarPajaroAzul(Punto2D p, Velocidad2D v) {
	/* TODO Implementar de manera similar a PajaroRojo
	 *
	 */
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
	HuevoBlanco* huevo = new HuevoBlanco(body, jugador);
	this->disparos.push_back(huevo);
	// Notifico al observador que se lanzo un huevo blanco
	if (this->observador != NULL)
		this->observador->seLanzoHuevoBlanco(huevo);
}

void Escenario::lanzarHuevosCodorniz(Punto2D p, Velocidad2D v, unsigned int j) {
	/* TODO implementar de manera similar a HuevoBlanco, pero tener en cuenta
	 * que se lanzan de a 3 Huevos de Codorniz
	 */
}

void Escenario::lanzarHuevoPoche(Punto2D p, Velocidad2D v, unsigned int j) {
	/* TODO implementar de manera similar a HuevoBlanco
	 */
}

void Escenario::lanzarHuevoReloj(Punto2D p, Velocidad2D v, unsigned int j) {
	/* TODO implementar de manera similar a HuevoBlanco
	 */
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
			this->escenario->DestroyBody(node);
			this->limpiarEnListas(cuerpo);
		}
		node = node->GetNext();
	}
}

void Escenario::limpiarEnListas(CuerpoAbstracto* cuerpo) {
	// Casteo como Disparo (más frecuente de morir)
	Disparo* dis = dynamic_cast<Disparo*>(cuerpo);
	if (dis != NULL) {
		this->disparos.remove(dis);
	} else {
		// Casteo como Pajaro (más frecuente después de disparo)
		Pajaro* paj = dynamic_cast<Pajaro*>(cuerpo);
		if (paj != NULL) {
			this->pajaros.remove(paj);
		} else {
			// Casteo como Fruta
			Fruta* fru = dynamic_cast<Fruta*>(cuerpo);
			if (fru != NULL) {
				this->frutas.remove(fru);
			} else {
				// Casteo como Superficie (Menos frecuente)
				Superficie* sup = dynamic_cast<Superficie*>(cuerpo);
				if (sup != NULL) {
					this->superficies.remove(sup);
				}
			}
		}
	}
	delete cuerpo;
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
