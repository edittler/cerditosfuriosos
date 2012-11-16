#include "EntradaPajaros.h"

EntradaPajaros::EntradaPajaros(int anchoEscenario, int altoEscenario):
	Frame("ENTRADA DE LOS PÁJAROS")
{
	float maximoX = (((anchoEscenario-1)*70)/100);
	float maximoY = (((altoEscenario-1)*70)/100);
	
	// Ajustes
	Gtk::Adjustment* ajusteXInicial = manage(new Gtk::Adjustment(1.0, 0.0, maximoX));
	Gtk::Adjustment* ajusteYInicial = manage(new Gtk::Adjustment(1.0, 0.0, maximoY));
	
	Gtk::Adjustment* ajusteXFinal = manage(new Gtk::Adjustment(1.0, 0.0, maximoX));
	Gtk::Adjustment* ajusteYFinal = manage(new Gtk::Adjustment(1.0, 0.0, maximoY));
	
	Gtk::Adjustment* ajusteTiempo = manage(new Gtk::Adjustment(1.0, 
													TIEMPO_GENERACION_MINIMO,
													TIEMPO_GENERACION_MAXIMO));
	Gtk::Adjustment* ajusteGeneracion = manage(new Gtk::Adjustment(1.0, 0.0, 100.0));
	Gtk::Adjustment* ajusteRojo = manage(new Gtk::Adjustment(0.0, 0.0, 100.0));
	Gtk::Adjustment* ajusteVerde = manage(new Gtk::Adjustment(0.0, 0.0, 100.0));
	Gtk::Adjustment* ajusteAzul = manage(new Gtk::Adjustment(0.0, 0.0, 100.0));
	// Widgets con funcionalidad
	xInicial = new Gtk::SpinButton(*ajusteXInicial);
	xInicial->set_value(maximoX);
	yInicial = new Gtk::SpinButton(*ajusteYInicial);
	xFinal = new Gtk::SpinButton(*ajusteXFinal);
	xFinal->set_value(maximoX);
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
	
	Gtk::Label* etiquetaUno = manage(new Gtk::Label("x inicial: "));
	Gtk::Label* etiquetaDos = manage(new Gtk::Label(" y inicial: "));
	cajaHorizontalUno->pack_start(*etiquetaUno);
	cajaHorizontalUno->pack_start(*xInicial);
	cajaHorizontalUno->pack_start(*etiquetaDos);
	cajaHorizontalUno->pack_start(*yInicial);
	
	Gtk::Label* etiquetaTres = manage(new Gtk::Label("x final: "));
	Gtk::Label* etiquetaCuatro = manage(new Gtk::Label(" y final: "));
	cajaHorizontalDos->pack_start(*etiquetaTres);
	cajaHorizontalDos->pack_start(*xFinal);
	cajaHorizontalDos->pack_start(*etiquetaCuatro);
	cajaHorizontalDos->pack_start(*yFinal);
	
	Gtk::Label* etiquetaCinco = manage(new Gtk::Label("Tiempo generación: "));
	Gtk::Label* etiquetaSeis = manage(new Gtk::Label(" ms"));
	cajaHorizontalTres->pack_start(*etiquetaCinco);
	cajaHorizontalTres->pack_start(*tiempoGeneracion);
	cajaHorizontalTres->pack_start(*etiquetaSeis);
	
	Gtk::Label* etiquetaSiete = manage(new Gtk::Label("Probabilidad generación: "));
	cajaHorizontalCuatro->pack_start(*etiquetaSiete);
	cajaHorizontalCuatro->pack_start(*probabilidadGeneracion);
	
	Gtk::Label* etiquetaOcho = manage(new Gtk::Label("Probabilidad pájaro rojo: "));
	cajaHorizontalCinco->pack_start(*etiquetaOcho);
	cajaHorizontalCinco->pack_start(*probabilidadRojo);
	
	Gtk::Label* etiquetaNueve = manage(new Gtk::Label("Probabilidad pájaro verde: "));
	cajaHorizontalSeis->pack_start(*etiquetaNueve);
	cajaHorizontalSeis->pack_start(*probabilidadVerde);
	
	Gtk::Label* etiquetaDiez = manage(new Gtk::Label("Probabilidad pájaro azul: "));
	cajaHorizontalSiete->pack_start(*etiquetaDiez);
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
	delete xInicial;
	delete yInicial;
	delete xFinal;
	delete yFinal;
	delete tiempoGeneracion;
	delete probabilidadGeneracion;
	delete probabilidadRojo;
	delete probabilidadVerde;
	delete probabilidadAzul;
}

bool EntradaPajaros::lineaEntradaValida() {
	return (yFinal->get_value_as_int() >= yInicial->get_value_as_int());
}

bool EntradaPajaros::porcentajesPajarosValidos() {
	return ((probabilidadRojo->get_value_as_int()+
			probabilidadVerde->get_value_as_int()+
			probabilidadAzul->get_value_as_int()) == 100);
}

float EntradaPajaros::getXInicioLineaEntrada() {
	return xInicial->get_value();
}		
		
float EntradaPajaros::getYInicioLineaEntrada() {
	return yInicial->get_value();
}		
		
float EntradaPajaros::getXFinalLineaEntrada() {
	return xFinal->get_value();
}		
		
float EntradaPajaros::getYFinalLineaEntrada() {
	return yFinal->get_value();
}		
		
int EntradaPajaros::getTiempoGeneracion() {
	return tiempoGeneracion->get_value_as_int();
}		
		
int EntradaPajaros::getProbabilidadGeneracion() {
	return probabilidadGeneracion->get_value_as_int();
}		
		
int EntradaPajaros::getProbabilidadPajaroRojo() {
	return probabilidadRojo->get_value_as_int();
}
		
int EntradaPajaros::getProbabilidadPajaroVerde() {
	return probabilidadVerde->get_value_as_int();
}

int EntradaPajaros::getProbabilidadPajaroAzul() {
	return probabilidadAzul->get_value_as_int();
}
