/*
 * Colisionador.cpp
 *
 *  Created on: 25/10/2012
 *      Author: ezequiel
 */
// Header Include.
#include "Colisionador.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"

#include <iostream> // FIXME borrar

Colisionador::Colisionador() {
	// TODO Auto-generated constructor stub

}

Colisionador::~Colisionador() {
	// TODO Auto-generated destructor stub
}

void Colisionador::BeginContact(b2Contact* contact) {
	/* TODO estudiar funcionamiento e implementar en caso de que sea necesario
	 */
	int16 catA = contact->GetFixtureA()->GetFilterData().categoryBits;
	int16 maskA = contact->GetFixtureA()->GetFilterData().maskBits;
	int16 catB = contact->GetFixtureB()->GetFilterData().categoryBits;
	int16 maskB = contact->GetFixtureB()->GetFilterData().maskBits;
	if (((catA & maskB) != 0) && ((catB & maskA) != 0)) {
		if ((catA == 1) || (catB == 1)) {
			std::cout << "\t*** CHOCO CONTRA EL PISO ***" << std::endl;
		} else {
			std::cout << "\t*** SE PRODUJO UN CHOQUE ***" << std::endl;
		}
	}
}

void Colisionador::EndContact(b2Contact* contact) {
	/* TODO Si choco algun huevo, este se debe destruir, avisando previamente
	 * a la vista.
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
