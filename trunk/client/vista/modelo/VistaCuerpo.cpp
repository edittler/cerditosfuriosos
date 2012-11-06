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
	x = ajustarValor(posicion.x);
	y = ajustarValor(posicion.y);
	escenario->mover(this, x, y);
}

void VistaCuerpo::seMurio() {
	escenario->eliminar(this);
}


int VistaCuerpo::ajustarValor(float valorFlotante) {
	valorFlotante *= 100;
	int valor = (int) round(valorFlotante);
	return valor;
}
