#include "VistaPajaroVerde.h"
#include "ConstantesVistaModelo.h"

// Forward Includes.
#include "VistaEscenario.h"

VistaPajaroVerde::VistaPajaroVerde(VistaEscenario* escenario,
		PajaroVerde* pajaro) : VistaCuerpo(escenario, pajaro,
		RUTA_PAJARO_VERDE_IZQ) {
	// Registro el observador en el modelo.
	pajaro->registrarObservador(this);
	// Obtengo la velocidad en x y selecciono la imagen a usar
	float velX = pajaro->getVelocidad().x;
	if (velX >= 0) {
		iniciarImagen(RUTA_PAJARO_VERDE_DER);
	}
}

VistaPajaroVerde::~VistaPajaroVerde() {
	// Elimino el observador en el modelo.
	this->cuerpo->eliminarObservador(this);
}

