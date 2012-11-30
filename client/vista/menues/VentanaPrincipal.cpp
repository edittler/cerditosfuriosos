#include "VentanaPrincipal.h"

#include <gtkmm/messagedialog.h>

#include "../modelo/ConstantesVistaModelo.h"

VentanaPrincipal::VentanaPrincipal() {
	set_title("Cerditos Furiosos");
	set_border_width(0);
	set_resizable(false);
	set_position(Gtk::WIN_POS_CENTER_ALWAYS);
	gdk_threads_init();
	contenedor = new Gtk::EventBox();
	add(*contenedor);
	panelInicial = new PanelInicial(ANCHO_VENTANA, ALTO_VENTANA,
														RUTA_FONDO_MENU, this);
	panelUnJugador = new PanelUnJugador(ANCHO_VENTANA, ALTO_VENTANA,
														RUTA_FONDO_MENU, this);
	panelMultijugador = new PanelMultijugador(ANCHO_VENTANA, ALTO_VENTANA,
														RUTA_FONDO_MENU, this);
	panelUnirsePartida = new PanelUnirsePartida(ANCHO_VENTANA, ALTO_VENTANA,
														RUTA_FONDO_MENU, this);
	panelCrearPartida = new PanelCrearPartida(ANCHO_VENTANA, ALTO_VENTANA,
														RUTA_FONDO_MENU, this);
	panelRecords = new PanelRecords(ANCHO_VENTANA, ALTO_VENTANA,
			RUTA_FONDO_MENU, this);
}

VentanaPrincipal::~VentanaPrincipal() {
	if (panelInicial != NULL)
		delete panelInicial;
	if (panelMultijugador!= NULL)
		delete panelMultijugador;
	if (panelRecords != NULL)
		delete panelRecords;
	if (panelCrearPartida != NULL)
		delete panelCrearPartida;
	if (panelUnirsePartida != NULL)
		delete panelUnirsePartida;
	delete panelUnJugador;
	delete contenedor;
}

void VentanaPrincipal::modoUnJugador() {
	remove();
	if (panelUnJugador == NULL)
		panelUnJugador = new PanelUnJugador(ANCHO_VENTANA, ALTO_VENTANA,
				RUTA_FONDO_MENU, this);
	add(*panelUnJugador);
	show_all_children();
}

void VentanaPrincipal::modoMultijugador() {
	remove();
	if (panelMultijugador == NULL)
		panelMultijugador = new PanelMultijugador(ANCHO_VENTANA, ALTO_VENTANA,
				RUTA_FONDO_MENU, this);
	add(*panelMultijugador);
	show_all_children();
}

void VentanaPrincipal::volverAMenuPrincipal() {
	remove();
	if (panelInicial == NULL)
		panelInicial = new PanelInicial(ANCHO_VENTANA, ALTO_VENTANA,
				RUTA_FONDO_MENU, this);
	add(*panelInicial);
	show_all_children();
}

void VentanaPrincipal::verRecords() {
	remove();
	if (panelRecords == NULL)
		panelRecords = new PanelRecords(ANCHO_VENTANA, ALTO_VENTANA,
					RUTA_FONDO_MENU, this);
	add(*panelRecords);
	show_all_children();
}

void VentanaPrincipal::agregarContenedor(Gtk::Widget& widget) {
	gdk_threads_enter();
	remove();
	contenedor->remove();
	contenedor->add(widget);
	add(*contenedor);
	show_all_children();
	gdk_threads_leave();
}

void VentanaPrincipal::vaciarContenedot() {
	gdk_threads_enter();
	contenedor->remove();
	gdk_threads_leave();
}

void VentanaPrincipal::setMouseListener(MouseListener* listener) {
	gdk_threads_enter();
		listener->cargarEventos(contenedor);
	gdk_threads_leave();
}

void VentanaPrincipal::modoCrearPartida(std::string nombreMundos) {
	if (get_child() != panelCrearPartida) {
		remove();
		if (panelCrearPartida == NULL)
			panelCrearPartida = new PanelCrearPartida(ANCHO_VENTANA,
										ALTO_VENTANA, RUTA_FONDO_MENU, this);
		panelCrearPartida->cargarMundos(nombreMundos);
		add(*panelCrearPartida);
		show_all_children();
	}
}

void VentanaPrincipal::modoUnirsePartida(std::string nombrePartidas) {
	if (get_child() != panelUnirsePartida) {
		remove();
		if (panelUnirsePartida == NULL)
			panelUnirsePartida = new PanelUnirsePartida(ANCHO_VENTANA,
					ALTO_VENTANA, RUTA_FONDO_MENU, this);
		panelUnirsePartida->cargarPartidas(nombrePartidas);
		add(*panelUnirsePartida);
		show_all_children();
	}
}

void VentanaPrincipal::mostrarMenuPrincipal() {
	gdk_threads_enter();
	remove();
	if (panelInicial == NULL)
		panelInicial = new PanelInicial(ANCHO_VENTANA, ALTO_VENTANA,
				RUTA_FONDO_MENU, this);
	add(*panelInicial);
	show_all_children();
	gdk_threads_leave();
}

void VentanaPrincipal::mostrarDialogo(std::string mensaje) {
	Gtk::MessageDialog dialogo(*this, mensaje);
	dialogo.run();
}
