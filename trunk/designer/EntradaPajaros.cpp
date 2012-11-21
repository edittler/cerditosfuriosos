// Header Include.
#include "EntradaPajaros.h"

// Constantes de probabilidades de pájaros por defecto
#define PROBABILIDAD_PAJARO_ROJO	50.0f
#define PROBABILIDAD_PAJARO_VERDE	30.0f
#define PROBABILIDAD_PAJARO_AZUL	20.0f

EntradaPajaros::EntradaPajaros(float anchoEscenario, float altoEscenario):
	Frame("ENTRADA DE LOS PÁJAROS") {
	xLineaEntrada = anchoEscenario;
	float maximoY = (altoEscenario-1);
	// Ajustes
	Gtk::Adjustment* ajusteYInicial = manage(new Gtk::Adjustment(1.0, 1.0,
			maximoY));
	Gtk::Adjustment* ajusteYFinal = manage(new Gtk::Adjustment(1.0, 0.0, maximoY));
	Gtk::Adjustment* ajusteTiempo = manage(new Gtk::Adjustment(1.0, 
													TIEMPO_GENERACION_MINIMO,
													TIEMPO_GENERACION_MAXIMO));
	Gtk::Adjustment* ajusteGeneracion = manage(new Gtk::Adjustment(1.0, 0.0,
			100.0));
	Gtk::Adjustment* ajusteRojo = manage(new Gtk::Adjustment(0.0, 0.0, 100.0));
	Gtk::Adjustment* ajusteVerde = manage(new Gtk::Adjustment(0.0, 0.0, 100.0));
	Gtk::Adjustment* ajusteAzul = manage(new Gtk::Adjustment(0.0, 0.0, 100.0));
	// Widgets con funcionalidad
	yInicial = new Gtk::SpinButton(*ajusteYInicial);
	yInicial->set_value(0);
	yFinal = new Gtk::SpinButton(*ajusteYFinal);
	yFinal->set_value(maximoY);
	tiempoGeneracion = new Gtk::SpinButton(*ajusteTiempo);
	tiempoGeneracion->set_value((TIEMPO_GENERACION_MAXIMO-
								TIEMPO_GENERACION_MINIMO) / 2);
	probabilidadGeneracion = new Gtk::SpinButton(*ajusteGeneracion);
	probabilidadGeneracion->set_value(50.0);
	probabilidadRojo = new Gtk::SpinButton(*ajusteRojo);
	probabilidadRojo->set_value(PROBABILIDAD_PAJARO_ROJO);
	probabilidadVerde = new Gtk::SpinButton(*ajusteVerde);
	probabilidadVerde->set_value(PROBABILIDAD_PAJARO_VERDE);
	probabilidadAzul = new Gtk::SpinButton(*ajusteAzul);
	probabilidadAzul->set_value(PROBABILIDAD_PAJARO_AZUL);
	// Contenedores
	Gtk::HBox* cajaHorizontalUno = manage(new Gtk::HBox(false, 0));
	Gtk::HBox* cajaHorizontalDos = manage(new Gtk::HBox(false, 0));
	Gtk::HBox* cajaHorizontalTres = manage(new Gtk::HBox(false, 0));
	Gtk::HBox* cajaHorizontalCuatro = manage(new Gtk::HBox(false, 0));
	Gtk::HBox* cajaHorizontalCinco = manage(new Gtk::HBox(false, 0));
	Gtk::HBox* cajaHorizontalSeis = manage(new Gtk::HBox(false, 0));
	Gtk::HBox* cajaHorizontalSiete = manage(new Gtk::HBox(false, 0));	
	Gtk::Label* etiquetaUno = manage(new Gtk::Label("y inicial: "));
	cajaHorizontalUno->pack_start(*etiquetaUno);
	cajaHorizontalUno->pack_start(*yInicial);
	Gtk::Label* etiquetaDos = manage(new Gtk::Label("y final: "));
	cajaHorizontalDos->pack_start(*etiquetaDos);
	cajaHorizontalDos->pack_start(*yFinal);
	Gtk::Label* etiquetaTres = manage(new Gtk::Label("Tiempo generación: "));
	Gtk::Label* etiquetaCuatro = manage(new Gtk::Label(" ms"));
	cajaHorizontalTres->pack_start(*etiquetaTres);
	cajaHorizontalTres->pack_start(*tiempoGeneracion);
	cajaHorizontalTres->pack_start(*etiquetaCuatro);
	Gtk::Label* etiquetaCinco = manage(new Gtk::Label(
			"Probabilidad generación: "));
	cajaHorizontalCuatro->pack_start(*etiquetaCinco);
	cajaHorizontalCuatro->pack_start(*probabilidadGeneracion);
	Gtk::Label* etiquetaSeis = manage(new Gtk::Label(
			"Probabilidad pájaro rojo: "));
	cajaHorizontalCinco->pack_start(*etiquetaSeis);
	cajaHorizontalCinco->pack_start(*probabilidadRojo);
	Gtk::Label* etiquetaSiete = manage(new Gtk::Label(
			"Probabilidad pájaro verde: "));
	cajaHorizontalSeis->pack_start(*etiquetaSiete);
	cajaHorizontalSeis->pack_start(*probabilidadVerde);
	Gtk::Label* etiquetaOcho = manage(new Gtk::Label(
			"Probabilidad pájaro azul: "));
	cajaHorizontalSiete->pack_start(*etiquetaOcho);
	cajaHorizontalSiete->pack_start(*probabilidadAzul);
	Gtk::Frame* cuadroEntrada = manage(new Gtk::Frame("Línea de entrada"));
	Gtk::Frame* cuadroGeneracion = manage(new Gtk::Frame(
			"Parámetros de generación"));
	Gtk::Frame* cuadroPajaros = manage(new Gtk::Frame(
			"Probabilidades de los pájaros"));
	Gtk::VBox* cajaVerticalUno = manage(new Gtk::VBox(false, 10));
	cajaVerticalUno->pack_start(*cajaHorizontalUno);
	cajaVerticalUno->pack_start(*cajaHorizontalDos);
	cuadroEntrada->add(*cajaVerticalUno);
	Gtk::VBox* cajaVerticalDos = manage(new Gtk::VBox(false, 10));
	cajaVerticalDos->pack_start(*cajaHorizontalTres);
	cajaVerticalDos->pack_start(*cajaHorizontalCuatro);
	cuadroGeneracion->add(*cajaVerticalDos);
	Gtk::VBox* cajaVerticalTres = manage(new Gtk::VBox(false, 10));
	cajaVerticalTres->pack_start(*cajaHorizontalCinco);
	cajaVerticalTres->pack_start(*cajaHorizontalSeis);
	cajaVerticalTres->pack_start(*cajaHorizontalSiete);
	cuadroPajaros->add(*cajaVerticalTres);
	Gtk::VBox* cajaVertical = manage(new Gtk::VBox(false, 20));
	cajaVertical->pack_start(*cuadroEntrada);
	cajaVertical->pack_start(*cuadroGeneracion);
	cajaVertical->pack_start(*cuadroPajaros);
	add(*cajaVertical);
}

EntradaPajaros::~EntradaPajaros() {
	delete yInicial;
	delete yFinal;
	delete tiempoGeneracion;
	delete probabilidadGeneracion;
	delete probabilidadRojo;
	delete probabilidadVerde;
	delete probabilidadAzul;
}

bool EntradaPajaros::lineaEntradaValida() const {
	return (yFinal->get_value_as_int() >= yInicial->get_value_as_int());
}

bool EntradaPajaros::porcentajesPajarosValidos() const {
	return ((probabilidadRojo->get_value_as_int()+
			probabilidadVerde->get_value_as_int()+
			probabilidadAzul->get_value_as_int()) == 100);
}
		
float EntradaPajaros::getYInicioLineaEntrada() const {
	return yInicial->get_value();
}
		
float EntradaPajaros::getYFinalLineaEntrada() const {
	return yFinal->get_value();
}		
		
int EntradaPajaros::getTiempoGeneracion() const {
	return tiempoGeneracion->get_value_as_int();
}		
		
int EntradaPajaros::getProbabilidadGeneracion() const {
	return probabilidadGeneracion->get_value_as_int();
}		
		
int EntradaPajaros::getProbabilidadPajaroRojo() const {
	return probabilidadRojo->get_value_as_int();
}
		
int EntradaPajaros::getProbabilidadPajaroVerde() const {
	return probabilidadVerde->get_value_as_int();
}

int EntradaPajaros::getProbabilidadPajaroAzul() const {
	return probabilidadAzul->get_value_as_int();
}

void EntradaPajaros::cargarNivel(const std::string rutaNivel) {
	// Abro el archivo del nivel
	XMLDocument doc;
	bool fileOpen = doc.LoadFile(rutaNivel);
	if (!fileOpen)
		return;

	// Obtengo el nodo raiz, que en teoría es el llamado Nivel. No lo valido.
	const XMLNode* root = doc.RootElement();

	// Obtengo el nodo de Linea de entrada derecha
	const XMLNode* nodoLinea = root->FirstChildElement("LineaEntradaDerecha");
	// Si el nodo no existe, salgo sin cargar nada
	if (nodoLinea == 0)
		return;
	// Obtengo los atributos de generacion
	double tiempGeneracion, probGeneracion;
	const char* aTG = nodoLinea->Attribute("tiempoGeneracion", &tiempGeneracion);
	const char* aPG = nodoLinea->Attribute("probabilidad", &probGeneracion);
	// Si el atributo "tiempoGeneracion" existe, lo cargo.
	if (aTG != 0)
		this->tiempoGeneracion->set_value(tiempGeneracion);
	// Si el atributo "probabilidad" existe, lo cargo.
	if (aPG != 0)
		this->probabilidadGeneracion->set_value(probGeneracion);

	// Obtengo el nodo de posicion y cargo los atributos de posicion.
	const XMLNode* nodoPosicion = nodoLinea->FirstChildElement("Posicion");
	// Si el nodo no es nulo, cargo los atributos
	if (nodoPosicion != 0) {
		double posYInicial, posYFinal;
		const char* aYI = nodoPosicion->Attribute("yInicial", &posYInicial);
		const char* aYF = nodoPosicion->Attribute("yFinal", &posYFinal);
		// Si el atributo "yInicial" existe, lo cargo.
		if (aYI != 0)
			this->yInicial->set_value(posYInicial);
		// Si el atributo "yFinal" existe, lo cargo.
		if (aYF != 0)
			this->yFinal->set_value(posYFinal);
	}

	// Obtengo el nodo de probabilidades de pajaros y cargo los atributos dados.
	const XMLNode* nodoProbabilidades = nodoLinea->
			FirstChildElement("ProbabilidadesPajaros");
	// Si el nodo no es nulo, cargo las probabilidades de pájaros.
	if (nodoProbabilidades != 0) {
		this->XMLCargarProbabilidadesPajaros(nodoProbabilidades);
	}
}

void EntradaPajaros::guardarNivel(const std::string rutaNivel) const {
	// Abro el archivo del nivel
	XMLDocument doc;
	bool fileOpen = doc.LoadFile(rutaNivel);
	if (!fileOpen)
		return;

	// Obtengo el nodo raiz, que en teoría es el llamado Nivel. No lo valido.
	XMLNode* root = doc.RootElement();

	// Creo el nodo LineaEntrada
	XMLNode* nodoLinea = new XMLNode("LineaEntradaDerecha");
	// El tiempo de generacion y la probabilidad como atributos.
	nodoLinea->SetAttribute("tiempoGeneracion",
			tiempoGeneracion->get_value_as_int());
	nodoLinea->SetAttribute("probabilidad",
			probabilidadGeneracion->get_value_as_int());

	// Creo el nodo posicion y le seteo los atributos
	XMLNode* nodoPosicion = new XMLNode("Posicion");
	nodoPosicion->SetAttribute("x", xLineaEntrada);
	nodoPosicion->SetAttribute("yInicial", yInicial->get_value_as_int());
	nodoPosicion->SetAttribute("yFinal", yFinal->get_value_as_int());
	nodoLinea->LinkEndChild(nodoPosicion);

	// Cargo el nodo de las probabilidades de pajaros.
	XMLNode* nodoProbabilidades = this->XMLSerializarProbabilidadesPajaros();
	nodoLinea->LinkEndChild(nodoProbabilidades);

	// Cargo el nodo de linea de entrada al nodo del nivel
	root->LinkEndChild(nodoLinea);

	// Guardo el documento
	doc.SaveFile();
}

XMLNode* EntradaPajaros::XMLSerializarProbabilidadesPajaros() const {
	// Creo el nodo que contendrá todas las probabilidades.
	XMLNode* nodoProbabilidades = new XMLNode("ProbabilidadesPajaros");
	// Creo los nodos de probabilidad de cada pajaro y seteo su atributo
	XMLNode* nodoPajRojo = new XMLNode("PajaroRojo");
	nodoPajRojo->SetAttribute("probabilidad",
			probabilidadRojo->get_value_as_int());
	XMLNode* nodoPajVerde = new XMLNode("PajaroVerde");
	nodoPajVerde->SetAttribute("probabilidad",
			probabilidadVerde->get_value_as_int());
	XMLNode* nodoPajAzul = new XMLNode("PajaroAzul");
	nodoPajAzul->SetAttribute("probabilidad",
			probabilidadAzul->get_value_as_int());
	// Linkeo todos estos nodos en el nodo de probabilidades.
	nodoProbabilidades->LinkEndChild(nodoPajRojo);
	nodoProbabilidades->LinkEndChild(nodoPajVerde);
	nodoProbabilidades->LinkEndChild(nodoPajAzul);
	return nodoProbabilidades;
}

void EntradaPajaros::XMLCargarProbabilidadesPajaros(
		const XMLNode* nodoPajaros) {
	// Obtengo el nodo del pajaro rojo.
	const XMLNode* nodoPajaro = nodoPajaros->FirstChildElement("PajaroRojo");
	// Si el nodo no es nulo, cargo la probabilidad
	if (nodoPajaro != 0) {
		double probPaj;
		const char* aP = nodoPajaro->Attribute("probabilidad", &probPaj);
		// Si el atributo no es nulo, lo cargo
		if (aP != 0)
			this->probabilidadRojo->set_value(probPaj);
	}
	
	// Obtengo el nodo del pajaro verde.
	nodoPajaro = nodoPajaros->FirstChildElement("PajaroVerde");
	// Si el nodo no es nulo, cargo la probabilidad
	if (nodoPajaro != 0) {
		double probPaj;
		const char* aP = nodoPajaro->Attribute("probabilidad", &probPaj);
		// Si el atributo no es nulo, lo cargo
		if (aP != 0)
			this->probabilidadVerde->set_value(probPaj);
	}
	
	// Obtengo el nodo del pajaro azul.
	nodoPajaro = nodoPajaros->FirstChildElement("PajaroAzul");
	// Si el nodo no es nulo, cargo la probabilidad
	if (nodoPajaro != 0) {
		double probPaj;
		const char* aP = nodoPajaro->Attribute("probabilidad", &probPaj);
		// Si el atributo no es nulo, lo cargo
		if (aP != 0)
			this->probabilidadAzul->set_value(probPaj);
	}
}
