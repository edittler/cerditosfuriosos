// Header Include.
#include "VistaCuerpo.h"
#include "ConstantesVistaModelo.h"

// C++ Library Includes.
#include <cmath>

// Forward Includes.
#include "VistaEscenario.h"

VistaCuerpo::VistaCuerpo(VistaEscenario* escenario, CuerpoAbstracto* cuerpo,
		const char* ruta) {
	// Almaceno la referencia de la VistaEscenario
	this->escenario = escenario;
	// Almaceno la referencia al CuerpoAbstracto asociado.
	this->cuerpo = cuerpo;
	// inicializo imagen
	this->iniciarImagen(ruta);
	// Obtengo la posicion del cuerpo y realizo el ajuste de valores.
	Punto2D p = cuerpo->getPosicion();
	this->x = this->ajustarValorX(p.x);
	this->y = this->ajustarValorY(p.y);
	this->escenario->put(*this, this->x, this->y);
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

void VistaCuerpo::iniciarImagen(const char* path) {
	// Obtengo las dimensiones de la imagen.
	Glib::RefPtr<Gdk::Pixbuf> buf = Gdk::Pixbuf::create_from_file(path);
	this->ancho = buf->get_width();
	this->alto = buf->get_height();

	if (AJUSTE_ESCALA_IMAGENES == 1)  // no es necesario escalar.
		return;

	// escalo la imagen
	int nuevoAncho = round(ancho / AJUSTE_ESCALA_IMAGENES);
	int nuevoAlto = round(alto / AJUSTE_ESCALA_IMAGENES);
	buf = buf->scale_simple(nuevoAncho, nuevoAlto, Gdk::INTERP_BILINEAR);
	// FIXME la documentacion aclara que usando este metodo
	// The Gtk::Image will not react to state changes
	// Aclarar que significa esto.
	// Si hago una llamada a this->get_pixbuf() da error.
	// Aclaro en caso de que haya errores mas adelante.
	set(buf);

	// guardo nuevas dimensiones
	this->ancho = nuevoAncho;
	this->alto = nuevoAlto;
}
