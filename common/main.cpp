/*
 * main.cpp
 *
 *  Created on: 26/10/2012
 *      Author: ezequiel
 */
#include <iostream>
#include "model/Escenario.h"

int main(int argc, char *argv[]) {
	Escenario escena;
	escena.agregarCajaMadera(1,1);
	escena.lanzarPajaroRojo(1, 2, 20, 0);
	escena.lanzarHuevoBlanco(4, 2, -20, -2);
	char c;
	for(int i = 0; i < 200; i++) {
		escena.correrTick();
		std::cin >> c;
	}

	return 0;
}


