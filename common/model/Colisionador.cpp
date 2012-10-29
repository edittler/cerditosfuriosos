/*
 * Colisionador.cpp
 *
 *  Created on: 25/10/2012
 *      Author: ezequiel
 */
// Header Include.
#include "Colisionador.h"

// Box2D Library Includes.
#include "Box2D/Dynamics/Contacts/b2Contact.h"

// Project Includes.
#include "ConstantesColisiones.h"
#include "Superficie.h"
#include "Pajaro.h"
#include "Disparo.h"

#include <iostream> // FIXME borrar

Colisionador::Colisionador() {
	// TODO Auto-generated constructor stub

}

Colisionador::~Colisionador() {
	// TODO Auto-generated destructor stub
}

void Colisionador::BeginContact(b2Contact* contact) {
	// Obtengo las categorias y mascaras de los objetos que colisionaron
	int16 catA = contact->GetFixtureA()->GetFilterData().categoryBits;
	int16 maskA = contact->GetFixtureA()->GetFilterData().maskBits;
	int16 catB = contact->GetFixtureB()->GetFilterData().categoryBits;
	int16 maskB = contact->GetFixtureB()->GetFilterData().maskBits;
	if (((catA & maskB) != 0) && ((catB & maskA) != 0)) {
		// La categoria 1 es la default, la ignoro
		if ((catA != 1) && (catB != 1)) {
			// Casteo el dato del usuario como CuerpoAbstracto
			CuerpoAbstracto* cuerpoA = (CuerpoAbstracto*) contact->GetFixtureA()->GetBody()->GetUserData();
			CuerpoAbstracto* cuerpoB = (CuerpoAbstracto*) contact->GetFixtureB()->GetBody()->GetUserData();
			int16 sumCat = catA + catB;
			switch (sumCat) {
			case SUPERFICIE_AND_PAJARO:
				std::cout << "\t*** CHOCO PAJARO Y SUPERFICIE ***" << std::endl;
				this->chocarPajaroConSuperficie(cuerpoA, cuerpoB);
				break;
			case SUPERFICIE_AND_DISPARO:
				std::cout << "\t*** CHOCO DISPARO Y SUPERFICIE ***" << std::endl;
				break;
			case PAJARO_AND_DISPARO:
				std::cout << "\t*** CHOCO PAJARO Y DISPARO ***" << std::endl;
				this->chocarDisparoConPajaro(cuerpoA, cuerpoB);
				break;
			case CERDITO_AND_PAJARO:
				std::cout << "\t*** CHOCO PAJARO Y CERDITO ***" << std::endl;
				break;
			case CERDITO_AND_DISPARO:
				std::cout << "\t*** CHOCO DISPARO Y CERDITO ***" << std::endl;
				break;
			case MONTICULO_AND_PAJARO:
				std::cout << "\t*** CHOCO PAJARO Y MONTICULO ***" << std::endl;
				break;
			case MONTICULO_AND_DISPARO:
				std::cout << "\t*** CHOCO DISPARO Y MONTICULO ***" << std::endl;
				break;
			default:
				std::cout << "\t*** SE PRODUJO UN CHOQUE NO IDENTIFICADO ***" << std::endl;
				break;
			}
		} else {
			std::cout << "\t*** CHOCO CONTRA EL PISO ***" << std::endl;
		}
	}
}

void Colisionador::EndContact(b2Contact* contact) {
	/* TODO Si algun cuerpo de los que colisionaron quedo sin vida, este se debe
	 * eliminar de la escena, avisando previamente a la vista.
	 */
	/* TODO Si colisiono un huevo con una superficie y la superficie quedo sin
	 * vida, se debe asignar los puntajes al cerdito correspondiente.
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

void Colisionador::chocarPajaroConSuperficie(CuerpoAbstracto* cuerpoA, CuerpoAbstracto* cuerpoB) {
	Superficie* superficie = dynamic_cast<Superficie*>(cuerpoA);
	Pajaro* pajaro;
	if (!superficie) {
		superficie = dynamic_cast<Superficie*>(cuerpoB);
		pajaro = dynamic_cast<Pajaro*>(cuerpoA);
	} else {
		pajaro = dynamic_cast<Pajaro*>(cuerpoB);
	}
	pajaro->chocarCon(superficie);
}

void Colisionador::chocarDisparoConPajaro(CuerpoAbstracto* cuerpoA, CuerpoAbstracto* cuerpoB) {
	Disparo* disparo = dynamic_cast<Disparo*>(cuerpoA);
	Pajaro* pajaro;
	if (!disparo) {
		disparo = dynamic_cast<Disparo*>(cuerpoB);
		pajaro = dynamic_cast<Pajaro*>(cuerpoA);
	} else {
		pajaro = dynamic_cast<Pajaro*>(cuerpoB);
	}
	disparo->chocarCon(pajaro);
}
