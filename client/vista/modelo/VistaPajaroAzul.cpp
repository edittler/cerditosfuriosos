#include "VistaPajaroAzul.h"
#include "ConstantesVistaModelo.h"

// Forward Includes.
#include "VistaEscenario.h"

VistaPajaroAzul::VistaPajaroAzul(VistaEscenario* escenario,
		PajaroAzul* pajaro) : VistaCuerpo(escenario, pajaro,
		RUTA_PAJARO_AZUL_IZQ) {
	// Registro el observador en el modelo.
	pajaro->registrarObservador(this);
	// Obtengo la velocidad en x y selecciono la imagen a usar
	float velX = pajaro->getVelocidad().x;
	if (velX >= 0) {
		iniciarImagen(RUTA_PAJARO_AZUL_DER);
	}
}

VistaPajaroAzul::~VistaPajaroAzul() {
	// Elimino el observador en el modelo.
	this->cuerpo->eliminarObservador(this);
}

