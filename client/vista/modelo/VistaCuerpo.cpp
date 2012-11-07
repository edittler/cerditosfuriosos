// Header Include.
#include "VistaCuerpo.h"
#include "ConstantesVistaModelo.h"

// C++ Library Includes.
#include <cmath>

// Forward Includes.
#include "VistaEscenario.h"

VistaCuerpo::VistaCuerpo(VistaEscenario* escenario, CuerpoAbstracto* cuerpo,
		const char* ruta) : Gtk::Image(ruta) {
	// Almaceno la referencia de la VistaEscenario
	this->escenario = escenario;
	// Almaceno la referencia al CuerpoAbstracto asociado.
	this->cuerpo = cuerpo;
	// Obtengo la posicion del cuerpo y realizo el ajuste de valores.
	Punto2D p = cuerpo->getPosicion();
	this->x = this->ajustarValorX(p.x);
	this->y = this->ajustarValorY(p.y);
	this->escenario->put(*this, this->x, this->y);
	// Obtengo las dimensiones de la imagen.
	this->ancho = this->get_pixbuf()->get_width();
	this->alto = this->get_pixbuf()->get_height();
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
	valorFlotante *= AJUSTE_ESCALA_VISTA;  // Multiplico por el factor de escala.
	int valor = (int) round(valorFlotante);  // Redondeo y convierto a int.
	valor -= (ancho/2);  // Centro la imagen en la coordenada (eje X).
	return valor;
}

int VistaCuerpo::ajustarValorY(float valorFlotante) {
	valorFlotante *= AJUSTE_ESCALA_VISTA;  // Multiplico por el factor de escala.
	int valor = (int) round(valorFlotante);  // Redondeo y convierto a int.
	valor = this->escenario->getAlto() - valor;  // Ajusto la posicion vertical.
	valor -= (alto/2);  // Centro la imagen en la coordenada (eje y).
	return valor;
}
