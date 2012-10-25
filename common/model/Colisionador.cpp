/*
 * Colisionador.cpp
 *
 *  Created on: 25/10/2012
 *      Author: ezequiel
 */

#include "Colisionador.h"

Colisionador::Colisionador() {
	// TODO Auto-generated constructor stub

}

Colisionador::~Colisionador() {
	// TODO Auto-generated destructor stub
}

void Colisionador::BeginContact(b2Contact* contact) {
	/* TODO estudiar funcionamiento e implementar en caso de que sea necesario
	 */
}

void Colisionador::EndContact(b2Contact* contact) {
	/* TODO estudiar funcionamiento e implementar en caso de que sea necesario
	 */
}

void Colisionador::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	/* TODO estudiar funcionamiento e implementar en caso de que sea necesario
	 */
}

void Colisionador::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
	/* TODO estudiar funcionamiento e implementar en caso de que sea necesario
	 */
}
