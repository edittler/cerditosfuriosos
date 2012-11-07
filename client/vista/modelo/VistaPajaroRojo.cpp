// Header Include.
#include "VistaPajaroRojo.h"

// Project Includes.
#include "ConstantesVistaModelo.h"

// Forward Includes.
#include "VistaEscenario.h"

VistaPajaroRojo::VistaPajaroRojo(VistaEscenario* escenario,
		PajaroRojo* pajaro) : VistaCuerpo(escenario, pajaro,
		RUTA_PAJARO_ROJO_IZQ)
{
	// Registro el observador en el modelo.
	pajaro->registrarObservador(this);
	// Obtengo la posicion del cuerpo y realizo el ajuste de valores.
	Punto2D p = pajaro->getPosicion();
	this->x = this->ajustarValorX(p.x);
	this->y = this->ajustarValorY(p.y);
	this->escenario->put(*this, this->x, this->y);
	// Obtengo la velocidad en x y selecciono la imagen a usar
	float velX = pajaro->getVelocidad().x;
	if (velX >= 0) {
		this->set(RUTA_PAJARO_ROJO_DER);
	}
}

VistaPajaroRojo::~VistaPajaroRojo() {
	// Elimino el observador en el modelo.
	this->cuerpo->eliminarObservador(this);
}

