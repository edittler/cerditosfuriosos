// Header Include.
#include "NivelServer.h"

// C++ Library Project
#include <unistd.h>

// Project Includes
#include "XMLTypes.h"
#include "ConstantesServer.h"

NivelServer::NivelServer() {
	this->tiempoGeneracionMinimo = 250;
	this->tiempoAcumulado = 0;
	escenario = new Escenario();
	simulador = NULL;
}

NivelServer::~NivelServer() {
	delete escenario;
}

void NivelServer::tick(int milisegundos) {
	tiempoAcumulado += milisegundos;

	if (tiempoAcumulado >= tiempoGeneracionMinimo) {
		tiempoAcumulado -= tiempoGeneracionMinimo;
		this->generarPajaro();
	}

	escenario->correrTick();

	// FIXME manejar sleep igual que en NivelLocal????
	usleep(SERVER_DELTA_LOOP);
}

void NivelServer::lanzarHuevo(TipoDisparo tDisparo, Punto2D posInicial,
		Velocidad2D velInicial, unsigned int idJugador) {
	switch (tDisparo) {
	case T_HUEVO_BLANCO:
		escenario->lanzarHuevoBlanco(posInicial, velInicial, idJugador);
		break;
	case T_HUEVO_CODORNIZ:
		escenario->lanzarHuevosCodorniz(posInicial, velInicial, idJugador);
		break;
	case T_HUEVO_POCHE:
		escenario->lanzarHuevoPoche(posInicial, velInicial, idJugador);
		break;
	case T_HUEVO_RELOJ:
		escenario->lanzarHuevoReloj(posInicial, velInicial, idJugador);
		break;
	default:
		// No realizo nada.
		break;
	}
}

void NivelServer::lanzarHuevo(Punto2D p, Velocidad2D v, unsigned int j) {
	// TODO implementar
}

bool NivelServer::comienzoPartida() {
	return this->escenario->jugadoresCompletos();
}

bool NivelServer::finalizoPartida() const {
	return this->escenario->finalizoPartida();
}

void NivelServer::generarPajaro() {
	Punto2D punto;
	Velocidad2D velocidad;
	int tipoPajaro = simulador->generarPajaro(punto, velocidad);

	if (tipoPajaro != NO_PAJARO) {
		switch (tipoPajaro) {
		case PAJARO_AZUL: {
			Evento e(T_PAJARO_AZUL, punto, velocidad);
			this->colaMensajes.encolar(e);
			escenario->lanzarPajaroAzul(punto, velocidad);
			break; }
		case PAJARO_ROJO: {
			Evento e(T_PAJARO_ROJO, punto, velocidad);
			this->colaMensajes.encolar(e);
			escenario->lanzarPajaroRojo(punto, velocidad);
			break; }
		case PAJARO_VERDE: {
			Evento e(T_PAJARO_VERDE, punto, velocidad);
			this->colaMensajes.encolar(e);
			escenario->lanzarPajaroVerde(punto, velocidad);
			break; }
		}
	}
}

bool NivelServer::hayEventos() {
	return !this->colaMensajes.estaVacia();
}

Evento NivelServer::obtenerEvento() {
	return this->colaMensajes.obtenerFrente();
}

void NivelServer::cargarSimulador(const XMLNode* nodo) {
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

void NivelServer::XMLCargarProbabilidadesPajaros(const XMLNode* nodoPajaros,
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
