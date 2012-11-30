// Header Include.
#include "NivelLocal.h"

// C++ Library Project
#include <unistd.h>

// Project Includes.
#include "Constantes.h"
#include "../vista/modelo/ConstantesVistaModelo.h"

NivelLocal::NivelLocal() {
	this->tiempoGeneracionMinimo = 250;
	this->tiempoAcumulado = 0;
	escenario = new Escenario();
	simulador = NULL;
}

NivelLocal::~NivelLocal() {
	delete escenario;
	delete simulador;
}

void NivelLocal::tick(int milisegundos) {	
	tiempoAcumulado += milisegundos;

	if (tiempoAcumulado >= tiempoGeneracionMinimo) {
		tiempoAcumulado -= tiempoGeneracionMinimo;
		this->generarPajaro();
	}

	escenario->correrTick();
	usleep(DELTA_LOOP);
}

void NivelLocal::lanzarHuevo(Punto2D p, Velocidad2D v, unsigned int j) {
	int huevo = simulador->generarHuevo();

	switch (huevo) {
	case HUEVO_BLANCO:
		this->escenario->lanzarHuevoBlanco(p, v, j);
		break;
	case HUEVO_CODORNIZ:
		this->escenario->lanzarHuevosCodorniz(p, v, j);
		break;
	case HUEVO_POCHE:
		this->escenario->lanzarHuevoPoche(p, v, j);
		break;
	case HUEVO_RELOJ:
		this->escenario->lanzarHuevoReloj(p, v, j);
		break;
	default:
		this->lanzarHuevo(p, v, j);
		break;
	}
}

bool NivelLocal::finalizoPartida() const {
	return escenario->finalizoPartida();
}

void NivelLocal::cargarSimulador(const XMLNode* nodo) {
	// Si el nodo es nulo, cargo un simulador con valores por defecto
	if (nodo == NULL) {
		this->simulador = new Simulador();
		return;
	}

	// Obtengo los atributos de generacion
	int tiempGeneracion, probGeneracion;
	const char* aTG = nodo->Attribute("tiempoGeneracion", &tiempGeneracion);
	const char* aPG = nodo->Attribute("probabilidad", &probGeneracion);
	// Si el atributo "tiempoGeneracion" existe, lo cargo.
	if (aTG != 0)
		this->tiempoGeneracionMinimo = tiempGeneracion;
	// Si el atributo "probabilidad" no existe, seteo el valor en 0.
	if (aPG == 0)
		probGeneracion = 0;

	// Obtengo el nodo de posicion y cargo los atributos de posicion.
	const XMLNode* nodoPosicion = nodo->FirstChildElement("Posicion");
	// Si el nodo no es nulo, cargo los atributos
	double posX, posYInicial, posYFinal;
	if (nodoPosicion != 0) {
		const char* aX = nodoPosicion->Attribute("x", &posX);
		const char* aYI = nodoPosicion->Attribute("yInicial", &posYInicial);
		const char* aYF = nodoPosicion->Attribute("yFinal", &posYFinal);
		// Si el atributo "x" no existe, lo seteo en 0.
		if (aX == 0)
			posX = 0;
		// Si el atributo "yInicial" no existe, lo seteo en 0.
		if (aYI == 0)
			posYInicial = 0;
		// Si el atributo "yFinal" no existe, lo seteo en 0.
		if (aYF == 0)
			posYFinal = 0;
	}

	// Obtengo el nodo de probabilidades de pajaros y cargo los atributos dados.
	const XMLNode* nodoProbabilidades = nodo->
			FirstChildElement("ProbabilidadesPajaros");
	// Si el nodo no es nulo, cargo las probabilidades de pájaros.
	int pRojo, pVerde, pAzul;
	if (nodoProbabilidades != 0) {
		this->XMLCargarProbabilidadesPajaros(nodoProbabilidades, pRojo, pVerde,
				pAzul);
	}
	if (simulador != NULL)
		delete simulador;
	simulador = new Simulador(probGeneracion, pRojo, pVerde, pAzul, posX,
			posYInicial, posYFinal);
}

void NivelLocal::generarPajaro() {
	Punto2D punto;
	Velocidad2D velocidad;
	int tipoPajaro = simulador->generarPajaro(punto, velocidad);

	if (tipoPajaro != NO_PAJARO) {
		switch (tipoPajaro) {
		case PAJARO_AZUL:
			escenario->lanzarPajaroAzul(punto, velocidad);
			break;
		case PAJARO_ROJO:
			escenario->lanzarPajaroRojo(punto, velocidad);
			break;
		case PAJARO_VERDE:
			escenario->lanzarPajaroVerde(punto, velocidad);
			break;
		}
	}
}

void NivelLocal::XMLCargarProbabilidadesPajaros(const XMLNode* nodoPajaros,
		int& pRojo, int& pVerde, int& pAzul) {
	// Obtengo el nodo del pajaro rojo.
	const XMLNode* nodoPajaro = nodoPajaros->FirstChildElement("PajaroRojo");
	// Si el nodo no es nulo, cargo la probabilidad
	if (nodoPajaro != 0) {
		nodoPajaro->Attribute("probabilidad", &pRojo);
	}

	// Obtengo el nodo del pajaro verde.
	nodoPajaro = nodoPajaros->FirstChildElement("PajaroVerde");
	// Si el nodo no es nulo, cargo la probabilidad
	if (nodoPajaro != 0) {
		nodoPajaro->Attribute("probabilidad", &pVerde);
	}

	// Obtengo el nodo del pajaro azul.
	nodoPajaro = nodoPajaros->FirstChildElement("PajaroAzul");
	// Si el nodo no es nulo, cargo la probabilidad
	if (nodoPajaro != 0) {
		nodoPajaro->Attribute("probabilidad", &pAzul);
	}
}
