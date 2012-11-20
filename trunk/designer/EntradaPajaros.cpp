// Header Include.
#include "EntradaPajaros.h"

EntradaPajaros::EntradaPajaros(float anchoEscenario, float altoEscenario):
	Frame("ENTRADA DE LOS PÁJAROS") {
	xLineaEntrada = anchoEscenario;
	float maximoY = (altoEscenario-1);
	// Ajustes
	Gtk::Adjustment* ajusteYInicial = manage(new Gtk::Adjustment(1.0, 1.0, maximoY));
	Gtk::Adjustment* ajusteYFinal = manage(new Gtk::Adjustment(1.0, 0.0, maximoY));
	Gtk::Adjustment* ajusteTiempo = manage(new Gtk::Adjustment(1.0, 
													TIEMPO_GENERACION_MINIMO,
													TIEMPO_GENERACION_MAXIMO));
	Gtk::Adjustment* ajusteGeneracion = manage(new Gtk::Adjustment(1.0, 0.0, 100.0));
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
	probabilidadRojo->set_value(34.0);
	probabilidadVerde = new Gtk::SpinButton(*ajusteVerde);
	probabilidadVerde->set_value(33.0);
	probabilidadAzul = new Gtk::SpinButton(*ajusteAzul);
	probabilidadAzul->set_value(33.0);
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
	Gtk::Label* etiquetaCinco = manage(new Gtk::Label("Probabilidad generación: "));
	cajaHorizontalCuatro->pack_start(*etiquetaCinco);
	cajaHorizontalCuatro->pack_start(*probabilidadGeneracion);
	Gtk::Label* etiquetaSeis = manage(new Gtk::Label("Probabilidad pájaro rojo: "));
	cajaHorizontalCinco->pack_start(*etiquetaSeis);
	cajaHorizontalCinco->pack_start(*probabilidadRojo);
	Gtk::Label* etiquetaSiete = manage(new Gtk::Label("Probabilidad pájaro verde: "));
	cajaHorizontalSeis->pack_start(*etiquetaSiete);
	cajaHorizontalSeis->pack_start(*probabilidadVerde);
	Gtk::Label* etiquetaOcho = manage(new Gtk::Label("Probabilidad pájaro azul: "));
	cajaHorizontalSiete->pack_start(*etiquetaOcho);
	cajaHorizontalSiete->pack_start(*probabilidadAzul);
	Gtk::Frame* cuadroEntrada = manage(new Gtk::Frame("Línea de entrada"));
	Gtk::Frame* cuadroGeneracion = manage(new Gtk::Frame("Parámetros de generación"));
	Gtk::Frame* cuadroPajaros = manage(new Gtk::Frame("Probabilidades de los pájaros"));
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
	/*
	 * Informacion para Eze:
	 * 
	 * Aca se cargan de un nivel cuya ruta se pasa por parametro los valores
	 * correspondientes a la entrada de los pajaros, que estan en los siguientes
	 * widgets:
	 * 
	 * Gtk::SpinButton* yInicial;
	 * Gtk::SpinButton* yFinal;
	 * Gtk::SpinButton* tiempoGeneracion;
	 * Gtk::SpinButton* probabilidadGeneracion;
	 * Gtk::SpinButton* probabilidadRojo;
	 * Gtk::SpinButton* probabilidadVerde;
	 * Gtk::SpinButton* probabilidadAzul;
	 * 
	 * Para setearle a cada uno su correspondiente valor les podes invocar:
	 * ->set_value(float);
	 */
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
	/* FIXME Corregir por atributo x correspondiente que equivale al ancho del
	 * escenario.
	 */
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
