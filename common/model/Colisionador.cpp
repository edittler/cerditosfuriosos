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
			case CERDITO_AND_PAJARO:
				std::cout << "\t*** CHOCO PAJARO Y CERDITO ***" << std::endl;
				this->chocarPajaroConCerdito(cuerpoA, cuerpoB);
				break;
			case MONTICULO_AND_PAJARO:
				std::cout << "\t*** CHOCO PAJARO Y MONTICULO ***" << std::endl;
				this->chocarPajaroConMonticulo(cuerpoA, cuerpoB);
				break;
			case FRUTA_AND_PAJARO:
				std::cout << "\t*** CHOCO PAJARO Y FRUTA ***" << std::endl;
				this->chocarPajaroConFruta(cuerpoA, cuerpoB);
				break;
			case SUPERFICIE_AND_DISPARO:
				std::cout << "\t*** CHOCO DISPARO Y SUPERFICIE ***" << std::endl;
				this->chocarDisparoConSuperficie(cuerpoA, cuerpoB);
				break;
			case PAJARO_AND_DISPARO:
				std::cout << "\t*** CHOCO DISPARO Y PAJARO ***" << std::endl;
				this->chocarDisparoConPajaro(cuerpoA, cuerpoB);
				break;
			case CERDITO_AND_DISPARO:
				std::cout << "\t*** CHOCO DISPARO Y CERDITO ***" << std::endl;
				this->chocarDisparoConCerdito(cuerpoA, cuerpoB);
				break;
			case MONTICULO_AND_DISPARO:
				std::cout << "\t*** CHOCO DISPARO Y MONTICULO ***" << std::endl;
				this->chocarDisparoConMonticulo(cuerpoA, cuerpoB);
				break;
			case FRUTA_AND_DISPARO:
				std::cout << "\t*** CHOCO DISPARO Y FRUTA ***" << std::endl;
				this->chocarDisparoConFruta(cuerpoA, cuerpoB);
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
	if (superficie == NULL) {
		superficie = dynamic_cast<Superficie*>(cuerpoB);
		pajaro = dynamic_cast<Pajaro*>(cuerpoA);
	} else {
		pajaro = dynamic_cast<Pajaro*>(cuerpoB);
	}
	pajaro->chocarCon(superficie);
}

void Colisionador::chocarPajaroConCerdito(CuerpoAbstracto* cuerpoA, CuerpoAbstracto* cuerpoB) {
	Pajaro* pajaro = dynamic_cast<Pajaro*>(cuerpoA);
	Cerdito* cerdito;
	if (pajaro == NULL) {
		pajaro = dynamic_cast<Pajaro*>(cuerpoB);
		cerdito = dynamic_cast<Cerdito*>(cuerpoA);
	} else {
		cerdito = dynamic_cast<Cerdito*>(cuerpoB);
	}
	pajaro->chocarCon(cerdito);
}

void Colisionador::chocarPajaroConFruta(CuerpoAbstracto* cuerpoA, CuerpoAbstracto* cuerpoB) {
	Pajaro* pajaro = dynamic_cast<Pajaro*>(cuerpoA);
	Fruta* fruta;
	if (pajaro == NULL) {
		pajaro = dynamic_cast<Pajaro*>(cuerpoB);
		fruta = dynamic_cast<Fruta*>(cuerpoA);
	} else {
		fruta = dynamic_cast<Fruta*>(cuerpoB);
	}
	pajaro->chocarCon(fruta);
}

void Colisionador::chocarPajaroConMonticulo(CuerpoAbstracto* cuerpoA, CuerpoAbstracto* cuerpoB) {
	Pajaro* pajaro = dynamic_cast<Pajaro*>(cuerpoA);
	Monticulo* monticulo;
	if (pajaro == NULL) {
		pajaro = dynamic_cast<Pajaro*>(cuerpoB);
		monticulo = dynamic_cast<Monticulo*>(cuerpoA);
	} else {
		monticulo = dynamic_cast<Monticulo*>(cuerpoB);
	}
	pajaro->chocarCon(monticulo);
}

void Colisionador::chocarDisparoConSuperficie(CuerpoAbstracto* cuerpoA, CuerpoAbstracto* cuerpoB) {
	Disparo* disparo = dynamic_cast<Disparo*>(cuerpoA);
	Superficie* superficie;
	if (disparo == NULL) {
		disparo = dynamic_cast<Disparo*>(cuerpoB);
		superficie = dynamic_cast<Superficie*>(cuerpoA);
	} else {
		superficie = dynamic_cast<Superficie*>(cuerpoB);
	}
	disparo->chocarCon(superficie);
}

void Colisionador::chocarDisparoConPajaro(CuerpoAbstracto* cuerpoA, CuerpoAbstracto* cuerpoB) {
	Disparo* disparo = dynamic_cast<Disparo*>(cuerpoA);
	Pajaro* pajaro;
	if (disparo == NULL) {
		disparo = dynamic_cast<Disparo*>(cuerpoB);
		pajaro = dynamic_cast<Pajaro*>(cuerpoA);
	} else {
		pajaro = dynamic_cast<Pajaro*>(cuerpoB);
	}
	disparo->chocarCon(pajaro);
}

void Colisionador::chocarDisparoConCerdito(CuerpoAbstracto* cuerpoA, CuerpoAbstracto* cuerpoB) {
	Disparo* disparo = dynamic_cast<Disparo*>(cuerpoA);
	Cerdito* cerdito;
	if (disparo == NULL) {
		disparo = dynamic_cast<Disparo*>(cuerpoB);
		cerdito = dynamic_cast<Cerdito*>(cuerpoA);
	} else {
		cerdito = dynamic_cast<Cerdito*>(cuerpoB);
	}
	disparo->chocarCon(cerdito);
}

void Colisionador::chocarDisparoConMonticulo(CuerpoAbstracto* cuerpoA, CuerpoAbstracto* cuerpoB) {
	Disparo* disparo = dynamic_cast<Disparo*>(cuerpoA);
	Monticulo* monticulo;
	if (disparo == NULL) {
		disparo = dynamic_cast<Disparo*>(cuerpoB);
		monticulo = dynamic_cast<Monticulo*>(cuerpoA);
	} else {
		monticulo = dynamic_cast<Monticulo*>(cuerpoB);
	}
	disparo->chocarCon(monticulo);
}

void Colisionador::chocarDisparoConFruta(CuerpoAbstracto* cuerpoA, CuerpoAbstracto* cuerpoB) {
	Disparo* disparo = dynamic_cast<Disparo*>(cuerpoA);
	Fruta* fruta;
	if (disparo == NULL) {
		disparo = dynamic_cast<Disparo*>(cuerpoB);
		fruta = dynamic_cast<Fruta*>(cuerpoA);
	} else {
		fruta = dynamic_cast<Fruta*>(cuerpoB);
	}
	disparo->chocarCon(fruta);
}
