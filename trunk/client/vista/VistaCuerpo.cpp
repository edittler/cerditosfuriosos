// Header Include.
#include "VistaCuerpo.h"

// C++ Library Includes.
#include <cmath>

VistaCuerpo::VistaCuerpo() { }

VistaCuerpo::~VistaCuerpo() { }

int VistaCuerpo::ajustarValor(float valorFlotante) {
	valorFlotante *= 20;
	int valor = (int) round(valorFlotante);
	return valor;
}
