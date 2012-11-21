// Header Include.
#include "VistaPajaroRojo.h"

// Project Includes.
#include "ConstantesVistaModelo.h"

// Forward Includes.
#include "VistaEscenario.h"

VistaPajaroRojo::VistaPajaroRojo(VistaEscenario* escenario,
		PajaroRojo* pajaro) : VistaCuerpo(escenario, pajaro,
		RUTA_PAJARO_ROJO_IZQ) {
	// Registro el observador en el modelo.
	pajaro->registrarObservador(this);
	// Obtengo la velocidad en x y selecciono la imagen a usar
	float velX = pajaro->getVelocidad().x;
	if (velX >= 0) {
		iniciarImagen(RUTA_PAJARO_ROJO_DER);
	}
}

VistaPajaroRojo::~VistaPajaroRojo() {
	// Elimino el observador en el modelo.
	this->cuerpo->eliminarObservador(this);
}

