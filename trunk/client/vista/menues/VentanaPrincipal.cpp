#include "VentanaPrincipal.h"
#include "../modelo/ConstantesVistaModelo.h"
#include <iostream>
VentanaPrincipal::VentanaPrincipal() {
	set_title("Cerditos Furiosos");
	set_border_width(0);
	set_resizable(false);
	set_position(Gtk::WIN_POS_CENTER_ALWAYS);
//	std::string rutaFondo = "../../";
//	rutaFondo += RUTA_FONDO_MENU;
	panelInicial = new PanelInicial(ANCHO_VENTANA, ALTO_VENTANA, RUTA_FONDO_MENU,
																		this);
	panelUnJugador = NULL;
	panelMultijugador = NULL;
	panelUnirsePartida = NULL;
	panelRecords = NULL;
	add(*panelInicial);
	show_all_children();
}

VentanaPrincipal::~VentanaPrincipal() {
	delete panelInicial;
	if (panelUnJugador != NULL)
		delete panelUnJugador;
	if (panelMultijugador != NULL)
		delete panelMultijugador;
	if (panelUnirsePartida != NULL)
		delete panelUnirsePartida;
	if (panelRecords != NULL)
		delete panelRecords;
}

void VentanaPrincipal::modoUnJugador() {
	if (get_child() != panelUnJugador) {
		remove();
		if (panelUnJugador == NULL)
			panelUnJugador = new PanelUnJugador(ANCHO_VENTANA, ALTO_VENTANA,
					RUTA_FONDO_MENU, this);
		add(*panelUnJugador);
		show_all_children();
	}
}

void VentanaPrincipal::modoMultijugador() {
	if (get_child() != panelMultijugador) {
		remove();
		if (panelMultijugador == NULL)
			panelMultijugador = new PanelMultijugador(ANCHO_VENTANA, ALTO_VENTANA,
					RUTA_FONDO_MENU, this);
		add(*panelMultijugador);
		show_all_children();
	}
}

void VentanaPrincipal::volverAMenuPrincipal() {
	if (get_child() != panelInicial) {
		remove();
		if (panelInicial == NULL)
			panelInicial = new PanelInicial(ANCHO_VENTANA, ALTO_VENTANA,
					RUTA_FONDO_MENU, this);
		add(*panelInicial);
		show_all_children();
	}
}

void VentanaPrincipal::unirseAPartida() {
	if (get_child() != panelUnirsePartida) {
		remove();
		if (panelUnirsePartida == NULL)
			panelUnirsePartida = new PanelUnirsePartida(ANCHO_VENTANA, ALTO_VENTANA,
					RUTA_FONDO_MENU, this);
		add(*panelUnirsePartida);
		show_all_children();
	}
}

void VentanaPrincipal::verRecords() {
	if (get_child() != panelRecords) {
		remove();
		if (panelRecords == NULL)
			panelRecords = new PanelRecords(ANCHO_VENTANA, ALTO_VENTANA,
					RUTA_FONDO_MENU, this);
		add(*panelRecords);
		show_all_children();
	}
}
