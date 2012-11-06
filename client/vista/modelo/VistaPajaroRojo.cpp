// Header Include.
#include "VistaPajaroRojo.h"

// Project Includes.
#include "ConstantesVistaModelo.h"

// Forward Includes.
#include "VistaEscenario.h"

VistaPajaroRojo::VistaPajaroRojo(VistaEscenario* escenario,
		PajaroRojo* pajaro) : VistaCuerpo(escenario,RUTA_PAJARO_ROJO_IZQ) {
	// Obtengo la posicion, ajusto su valor y ubico la imagen en el escenario.
	Punto2D p = pajaro->getPosicion();
	this->x = this->ajustarValorX(p.x);
	this->y = this->ajustarValorY(p.y);
	pajaro->registrarObservador(this);
	this->escenario->put(*this, this->x, this->y);
	// Obtengo la velocidad en x y selecciono la imagen a usar
	float velX = pajaro->getVelocidad().x;
	if (velX >= 0) {
		this->set(RUTA_PAJARO_ROJO_DER);
	}
}

VistaPajaroRojo::~VistaPajaroRojo() {
	// TODO Auto-generated destructor stub
}

