// Header Include.
#include "VistaCerdito.h"

// Project Includes.
#include "ConstantesVistaModelo.h"

// Forward Includes.
#include "VistaEscenario.h"

VistaCerdito::VistaCerdito(VistaEscenario* escenario, Cerdito* cerdito):
	VistaCuerpo(escenario,RUTA_CERDITO) {
	Punto2D p = cerdito->getPosicion();
	this->x = this->ajustarValor(p.x);
	this->y = this->ajustarValor(p.y);
	this->escenario->put(*this, this->x, this->y);
}

VistaCerdito::~VistaCerdito() {}
