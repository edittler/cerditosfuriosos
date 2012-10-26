/*
 * HuevoBlanco.cpp
 *
 *  Created on: 26/10/2012
 *      Author: ezequiel
 */

// Header Include.
#include "HuevoBlanco.h"

// Double Dispatch Includes.
// SUPERFICIES
#include "CajaMadera.h"
// PAJAROS
#include "PajaroRojo.h"

HuevoBlanco::HuevoBlanco() {
	// TODO Auto-generated constructor stub

}

HuevoBlanco::~HuevoBlanco() {
	// TODO Auto-generated destructor stub
}

void HuevoBlanco::chocarCon(const CajaMadera* caja) {
	/* Al chocar con superficies, el Huevo Blanco explota, provocando un daño
	 * de 0.5 (cuyo calculo lo realiza la caja).
	 */
	this->vida = 0;
	// TODO Implementar explosion en la vista y que luego desaparezca.
}

void HuevoBlanco::chocarCon(const PajaroRojo* pajaro) {
	/* Al chocar con pajaros, genera un daño (cuyo calculo lo realiza el pajaro)
	 * y se destruye.
	 */
	this->vida = 0;
}

void HuevoBlanco::chocarCon(const HuevoBlanco* huevo) {
	/* Los huevos no se chocan entre si, pudiendo superponerse, por lo que no
	 * realizo nada.
	 */
}
