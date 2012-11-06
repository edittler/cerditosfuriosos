// Header Include.
#include "VistaEscenario.h"

// Forward Includes.
#include "VistaCuerpo.h"

//Project Includes.
#include "VistaCerdito.h"
#include "VistaPajaroRojo.h"

VistaEscenario::VistaEscenario(Escenario* escenario) {
	// Ajusto las dimensiones del fixed al tamaño del escenario.
	this->ancho = escenario->getAncho();
	this->alto = escenario->getAlto();
	this->set_size_request(ancho, alto);
	// Registro la vista del escenario en el escenario del modelo.
	escenario->registrarObservador(this);
	// Agrego el fondo en el fixed. TODO Implementar
}

VistaEscenario::~VistaEscenario() {}

void VistaEscenario::mover(VistaCuerpo* cuerpo, int x, int y) {
	this->move(*cuerpo, x, y);
}

void VistaEscenario::eliminar(VistaCuerpo* cuerpo) {
	this->remove(*cuerpo);
}

void VistaEscenario::seAgregoCerdito(Cerdito* cerdito) {
	VistaCerdito* vCerdito = new VistaCerdito(this, cerdito);
	cerdito->registrarObservador(vCerdito);
	show_all();
}

void VistaEscenario::seAgregoCatapulta(Catapulta* catapulta) {

}

void VistaEscenario::seAgregoMonticulo(Monticulo* monticulo) {

}

void VistaEscenario::seAgregoCajaVidrio(CajaVidrio* caja) {

}

void VistaEscenario::seAgregoCajaMadera(CajaMadera* caja) {

}

void VistaEscenario::seAgregoCajaMetal(CajaMetal* caja) {

}

void VistaEscenario::seAgregoManzana(Manzana* manzana) {

}

void VistaEscenario::seAgregoBanana(Banana* banana) {

}

void VistaEscenario::seAgregoCereza(Cereza* cereza) {

}

void VistaEscenario::seLanzoPajaroRojo(PajaroRojo* pajaro) {
	VistaPajaroRojo* vPajaro = new VistaPajaroRojo(this, pajaro);
	pajaro->registrarObservador(vPajaro);
	show_all();
}

void VistaEscenario::seLanzoPajaroVerde(PajaroVerde* pajaro) {

}

void VistaEscenario::seLanzoPajaroAzul(PajaroAzul* pajaro) {

}

void VistaEscenario::seLanzoHuevoBlanco(HuevoBlanco* huevo) {

}

void VistaEscenario::seLanzoHuevoCodorniz(HuevoCodorniz* huevo) {

}

void VistaEscenario::seLanzoHuevoPoche(HuevoPoche* huevo) {

}

void VistaEscenario::seLanzoHuevoReloj(HuevoReloj* huevo) {

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
void VistaEscenario::cerditoMatado(std::string nombreJugador) {

}

void VistaEscenario::partidaGanada() {

}

int VistaEscenario::getAncho() const {
	return this->ancho;
}
int VistaEscenario::getAlto() const {
	return this->alto;
}
