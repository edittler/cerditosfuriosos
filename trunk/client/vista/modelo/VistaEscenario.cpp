// Header Include.
#include "VistaEscenario.h"

// Forward Includes.
#include "VistaCuerpo.h"

//Project Includes.
#include "VistaCerdito.h"
#include "VistaCatapulta.h"
#include "VistaMonticulo.h"
#include "VistaCajaMadera.h"
#include "VistaCajaVidrio.h"
#include "VistaCajaMetal.h"
#include "VistaBanana.h"
#include "VistaCereza.h"
#include "VistaManzana.h"
#include "VistaPajaroRojo.h"
#include "VistaPajaroVerde.h"
#include "VistaPajaroAzul.h"
#include "VistaHuevoBlanco.h"
#include "VistaHuevoCodorniz.h"
#include "VistaHuevoPoche.h"
#include "VistaHuevoReloj.h"
#include "ConstantesVistaModelo.h"

// Exception Includes
#include "../excepciones/ImagenException.h"

VistaEscenario::VistaEscenario(Escenario* escenario) {
	// Almaceno el escenario
	this->escenario = escenario;
	// Registro la vista del escenario en el escenario del modelo.
	this->escenario->registrarObservador(this);
	// Establezco unas dimenciones estandar
	this->ancho = 1024;
	this->alto = 640;
	this->set_size_request(ancho, alto);
}

VistaEscenario::~VistaEscenario() {
	// Libero la memoria de las vistas
	std::list<VistaCuerpo*>::iterator it;
	for(it = this->vCuerpos.begin(); it != this->vCuerpos.end(); ++it) {
		delete (*it);
	}
}

void VistaEscenario::cargarEscenario() {
	// inicio las imagenes de fondo
	this->iniciarImagenFondo();
	this->iniciarImagenSuelo();
}

void VistaEscenario::mover(VistaCuerpo* cuerpo, int x, int y) {
	this->move(*cuerpo, x, y);
}

void VistaEscenario::eliminar(VistaCuerpo* cuerpo) {
	// Elimino el cuerpo del fixed
	this->remove(*cuerpo);
	// Elimino el cuerpo de la lista de vista de cuerpos
	this->vCuerpos.remove(cuerpo);
	// Elimino el cuerpo.
	delete cuerpo;
}

void VistaEscenario::seAjustoTamanio(float ancho, float alto) {
	// Ajusto las dimensiones del fixed al tamaño del escenario.
	this->ancho = ancho * AJUSTE_ESCALA_VISTA;
	this->alto = alto * AJUSTE_ESCALA_VISTA;
	this->set_size_request(this->ancho, this->alto);
}

void VistaEscenario::seEstablecioFondo() {
	this->iniciarImagenFondo();
}

void VistaEscenario::seEstablecioSuelo() {
	this->iniciarImagenSuelo();
}

void VistaEscenario::seAgregoCerdito(Cerdito* cerdito) {
	VistaCerdito* vCerdito = new VistaCerdito(this, cerdito);
	this->vCuerpos.push_back(vCerdito);
	show_all();
}

void VistaEscenario::seAgregoCatapulta(Catapulta* catapulta) {
	VistaCatapulta* vCatapulta = new VistaCatapulta(this, catapulta);
	this->vCuerpos.push_back(vCatapulta);
	show_all();
}

void VistaEscenario::seAgregoMonticulo(Monticulo* monticulo) {
	VistaMonticulo* vMonticulo = new VistaMonticulo(this, monticulo);
	this->vCuerpos.push_back(vMonticulo);
	show_all();
}

void VistaEscenario::seAgregoCajaVidrio(CajaVidrio* caja) {
	VistaCajaVidrio* vCaja = new VistaCajaVidrio(this, caja);
	this->vCuerpos.push_back(vCaja);
	show_all();
}

void VistaEscenario::seAgregoCajaMadera(CajaMadera* caja) {
	// FIXME usar manage para crear asi libera memoria automaticamente??
	// idem con todos los metodos.
	VistaCajaMadera* vCaja = new VistaCajaMadera(this, caja);
	this->vCuerpos.push_back(vCaja);
	show_all();
}

void VistaEscenario::seAgregoCajaMetal(CajaMetal* caja) {
	VistaCajaMetal* vCaja = new VistaCajaMetal(this, caja);
	this->vCuerpos.push_back(vCaja);
	show_all();
}

void VistaEscenario::seAgregoManzana(Manzana* manzana) {
        VistaManzana* vManzana = new VistaManzana(this, manzana);
	this->vCuerpos.push_back(vManzana);
	show_all();
}

void VistaEscenario::seAgregoBanana(Banana* banana) {
        VistaBanana* vBanana = new VistaBanana(this, banana);
	this->vCuerpos.push_back(vBanana);
	show_all();
}

void VistaEscenario::seAgregoCereza(Cereza* cereza) {
        VistaCereza* vCereza = new VistaCereza(this, cereza);
	this->vCuerpos.push_back(vCereza);
	show_all();
}

void VistaEscenario::seLanzoPajaroRojo(PajaroRojo* pajaro) {
	VistaPajaroRojo* vPajaro = new VistaPajaroRojo(this, pajaro);
	this->vCuerpos.push_back(vPajaro);
	show_all();
}

void VistaEscenario::seLanzoPajaroVerde(PajaroVerde* pajaro) {
	VistaPajaroVerde* vPajaro = new VistaPajaroVerde(this, pajaro);
	this->vCuerpos.push_back(vPajaro);
	show_all();
}

void VistaEscenario::seLanzoPajaroAzul(PajaroAzul* pajaro) {
	VistaPajaroAzul* vPajaro = new VistaPajaroAzul(this, pajaro);
	this->vCuerpos.push_back(vPajaro);
	show_all();
}

void VistaEscenario::seLanzoHuevoBlanco(HuevoBlanco* huevo) {
	VistaHuevoBlanco* vHuevo = new VistaHuevoBlanco(this, huevo);
	this->vCuerpos.push_back(vHuevo);
	show_all();
}

void VistaEscenario::seLanzoHuevoCodorniz(HuevoCodorniz* huevo) {
	VistaHuevoCodorniz* vHuevo = new VistaHuevoCodorniz(this, huevo);
	this->vCuerpos.push_back(vHuevo);
	show_all();
}

void VistaEscenario::seLanzoHuevoPoche(HuevoPoche* huevo) {
        VistaHuevoPoche* vHuevo = new VistaHuevoPoche(this, huevo);
	this->vCuerpos.push_back(vHuevo);
	show_all();
}

void VistaEscenario::seLanzoHuevoReloj(HuevoReloj* huevo) {
	VistaHuevoReloj* vHuevo = new VistaHuevoReloj(this, huevo);
	this->vCuerpos.push_back(vHuevo);
	show_all();
}

void VistaEscenario::monticuloDestruido() {

}

/* Metodo que será usado en el caso de que el escenario tenga un único cerdito.
 */
void VistaEscenario::cerditoMatado() {

}

/* Método que será usado en el caso multijugador, donde el escenario tiene
 * varios cerditos.
 * El parámetro es el nombre del jugador al que corresponde el cerdito matado.
 */
void VistaEscenario::cerditoMatado(unsigned int idJugador) {

}

void VistaEscenario::partidaGanada() {

}

void VistaEscenario::partidaPerdida() {

}

int VistaEscenario::getAncho() const {
	return this->ancho;
}
int VistaEscenario::getAlto() const {
	return this->alto;
}

void VistaEscenario::iniciarImagenFondo() {
	Glib::RefPtr<Gdk::Pixbuf> buf;
	try {
		buf = Gdk::Pixbuf::create_from_file(this->escenario->getRutaImagenFondo());
	} catch (Glib::FileError& e) {
		throw ImagenException("Error al cargar imagen de fondo.");
	}
	// escalo imagen
	buf = buf->scale_simple(ancho, alto, Gdk::INTERP_BILINEAR);

	// seteo nueva imgen
	this->fondo = new Gtk::Image(buf);
	this->put(*fondo, 0, 0);
}

void VistaEscenario::iniciarImagenSuelo() {
	Glib::RefPtr<Gdk::Pixbuf> buf;
	try {
		buf = Gdk::Pixbuf::create_from_file(this->escenario->getRutaImagenSuelo());
	} catch (Glib::FileError& e) {
		throw ImagenException("Error al cargar imagen del suelo.");
	}
	// escalo imagen
	int nuevoAlto = round((SUELO_ALTO + SUELO_POSICION) * AJUSTE_ESCALA_VISTA);
	buf = buf->scale_simple(ancho, nuevoAlto, Gdk::INTERP_BILINEAR);

	// seteo nueva imgen
	this->suelo =  new Gtk::Image(buf);
	this->put(*suelo, 0, alto - nuevoAlto);
}
