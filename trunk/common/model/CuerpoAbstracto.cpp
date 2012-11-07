// Header Include.
#include "CuerpoAbstracto.h"

// Exceptions Includes.
#include "exceptions/ObservadorException.h"

#include <cstdio>  // TODO PROVISORIO, BORRAR

CuerpoAbstracto::CuerpoAbstracto() {
	this->cuerpo = NULL;
	this->vida = 0;
	this->observador = NULL;
}

CuerpoAbstracto::CuerpoAbstracto(b2Body* cuerpo, float vida) {
	// Almaceno el b2Body correspondiente a Box2D
	this->cuerpo = cuerpo;
	// Almaceno la vida que va a tener el cuerpo
	this->vida = vida;
	// Establezco el observador como nulo.
	this->observador = NULL;

}

CuerpoAbstracto::~CuerpoAbstracto() {
	// TODO Auto-generated destructor stub
}

bool CuerpoAbstracto::estaVivo() const {
	if (this->vida <= 0)
		return false;
	return true;
}

void CuerpoAbstracto::daniar(float danio) {
	this->vida -= danio;
	// Si la vida resulta negativa, aviso al observador que el cuerpo se murio.
	if ((!this->estaVivo()) && (this->observador != 0)) {
		this->observador->seMurio();
	}
}

void CuerpoAbstracto::matar() {
	this->vida = 0;
	// Como se mató al cuerpo, aviso al observador.
	if (this->observador != 0) {
		this->observador->seMurio();
	}
}

void CuerpoAbstracto::registrarObservador(ObservadorCuerpo* observador) {
	/* Si el observador no es nulo, es porque ya hay uno registrado. Como no
	 * puede haber más de un observador, lanzo una excepcion.
	 */
	if (this->observador != NULL) {
		throw ObservadorException("El objeto ya tiene un observador.");
	}
	this->observador = observador;
}

void CuerpoAbstracto::eliminarObservador(ObservadorCuerpo* observador) {
	/* Si el observador que se quiere eliminar no coincide con el que se
	 * encuentra registrado, lanzo una excepcion.
	 */
	if (this->observador != observador) {
		throw ObservadorException("El observador no se encuentra registrado.");
	}
	this->observador = NULL;
}

void CuerpoAbstracto::notificarPosicionAObservador() {
	// Si el observador en no nulo, le envio la posicion.
	if (this->observador != NULL) {
		this->observador->actualizarPosicion(this->getPosicion());
	}
}

Punto2D CuerpoAbstracto::getPosicion() const{
	b2Vec2 vec = this->cuerpo->GetPosition();
	Punto2D p;
	p.x = vec.x;
	p.y = vec.y;
	return p;
}

Velocidad2D CuerpoAbstracto::getVelocidad() const {
	b2Vec2 vec = this->cuerpo->GetLinearVelocity();
	Velocidad2D v;
	v.x = vec.x;
	v.y = vec.y;
	return v;
}

void CuerpoAbstracto::printPosition() const {
	b2Vec2 position = this->cuerpo->GetPosition();
	printf("Cuerpo: x=%4.2f y=%4.2f  ", position.x, position.y);
}
