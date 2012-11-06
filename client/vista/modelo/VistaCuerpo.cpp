// Header Include.
#include "VistaCuerpo.h"

// C++ Library Includes.
#include <cmath>

// Forward Includes.
#include "VistaEscenario.h"

VistaCuerpo::VistaCuerpo(VistaEscenario* escenario, const char* ruta) :
Gtk::Image(ruta) {
	this->escenario = escenario;
}

VistaCuerpo::~VistaCuerpo() { }

void VistaCuerpo::actualizarPosicion(Punto2D posicion) {
	x = ajustarValorX(posicion.x);
	y = ajustarValorY(posicion.y);
	escenario->mover(this, x, y);
}

void VistaCuerpo::seMurio() {
	escenario->eliminar(this);
}

int VistaCuerpo::ajustarValorX(float valorFlotante) {
	valorFlotante *= 100;
	int valor = (int) round(valorFlotante);
	return valor;
}

int VistaCuerpo::ajustarValorY(float valorFlotante) {
	valorFlotante *= 100;
	int valor = (int) round(valorFlotante);
	valor = this->escenario->getAlto() - valor;
	return valor;
}
