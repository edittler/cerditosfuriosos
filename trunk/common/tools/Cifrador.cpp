// Header Include
#include "Cifrador.h"

Cifrador::Cifrador() { }

Cifrador::~Cifrador() { }

void Cifrador::cifrar(std::string& msj, int clave) {
	for (int i = 0; i < (int)msj.size(); ++i) {
		msj[i] += clave;
	}
}

void Cifrador::descifrar(std::string& msj, int clave) {
	cifrar(msj, -clave);
}
