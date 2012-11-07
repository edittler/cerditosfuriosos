// Header Include.
#include "VistaCerdito.h"

// Project Includes.
#include "ConstantesVistaModelo.h"

// Forward Includes.
#include "VistaEscenario.h"

VistaCerdito::VistaCerdito(VistaEscenario* escenario, Cerdito* cerdito):
	VistaCuerpo(escenario, cerdito, RUTA_CERDITO)
{
	// Registro el observador en el modelo.
	cerdito->registrarObservador(this);
	// Obtengo la posicion del cuerpo y realizo el ajuste de valores.
	Punto2D p = cerdito->getPosicion();
	this->x = this->ajustarValorX(p.x);
	this->y = this->ajustarValorY(p.y);
	this->escenario->put(*this, this->x, this->y);
}

VistaCerdito::~VistaCerdito() {
	// Elimino el observador del modelo
	this->cuerpo->eliminarObservador(this);
}
