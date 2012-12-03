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
											RUTA_FONDO_PANEL_INICIAL, *this);
	panelUnJugador = new PanelUnJugador(ANCHO_VENTANA, ALTO_VENTANA,
											RUTA_FONDO_PANEL_UN_JUGADOR, this);
	panelMultijugador = new PanelMultijugador(ANCHO_VENTANA, ALTO_VENTANA,
										RUTA_FONDO_PANEL_MULTIJUGADOR, *this);
	panelConfiguracion = new PanelConfiguracion(ANCHO_VENTANA, ALTO_VENTANA,
										RUTA_FONDO_PANEL_CONFIGURACION, this);
	panelCrearPartida = new PanelCrearPartida(ANCHO_VENTANA, ALTO_VENTANA,
										RUTA_FONDO_PANEL_CREAR_PARTIDA, *this);
	panelUnirsePartida = new PanelUnirsePartida(ANCHO_VENTANA, ALTO_VENTANA,
									RUTA_FONDO_PANEL_UNIRSE_PARTIDA, *this);
	panelEsperandoJugadores = new PanelEsperandoJugadores(ANCHO_VENTANA,
					ALTO_VENTANA, RUTA_FONDO_PANEL_ESPERANDO_JUGADORES, *this);
	panelRecords = new PanelRecords(ANCHO_VENTANA, ALTO_VENTANA,
											RUTA_FONDO_PANEL_RECORDS, this);
}

VentanaPrincipal::~VentanaPrincipal() {
	delete panelInicial;
	delete panelUnJugador;
	delete panelMultijugador;
	delete panelConfiguracion;void mostrarMenuMultijugador();
	delete panelCrearPartida;
	delete panelUnirsePartida;
	delete panelEsperandoJugadores;
	delete panelRecords;
	delete contenedor;
}

void VentanaPrincipal::modoUnJugador() {
	remove();
	add(*panelUnJugador);
	show_all_children();
}

void VentanaPrincipal::modoMultijugador() {
	remove();
	add(*panelMultijugador);
	show_all_children();
}

void VentanaPrincipal::modoConfiguracion(std::string direccion,
		unsigned short int puerto) {
	remove();
	panelConfiguracion->setearValores(direccion, puerto);
	add(*panelConfiguracion);
	show_all_children();
}

void VentanaPrincipal::volverAMenuPrincipal() {
	remove();
	add(*panelInicial);
	show_all_children();
}

void VentanaPrincipal::verRecords() {
	remove();
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

void VentanaPrincipal::vaciarContenedor() {
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
		panelCrearPartida->cargarMundos(nombreMundos);
		add(*panelCrearPartida);
		show_all_children();
	}
}

void VentanaPrincipal::modoUnirsePartida(std::string nombrePartidas) {
	if (get_child() != panelUnirsePartida) {
		remove();
		panelUnirsePartida->cargarPartidas(nombrePartidas);
		add(*panelUnirsePartida);
		show_all_children();
	}
}

void VentanaPrincipal::mostrarMenuPrincipal() {
	gdk_threads_enter();
	remove();
	add(*panelInicial);
	show_all_children();
	gdk_threads_leave();
}

void VentanaPrincipal::mostrarMenuMultijugador() {
	gdk_threads_enter();
	remove();
	add(*panelMultijugador);
	show_all_children();
	gdk_threads_leave();
}

void VentanaPrincipal::modoEsperandoJugadores() {
	if (get_child() != panelEsperandoJugadores) {
		remove();
		add(*panelEsperandoJugadores);
		show_all_children();
	}
}

void VentanaPrincipal::mostrarDialogo(std::string mensaje) {
	Gtk::MessageDialog dialogo(*this, mensaje);
	dialogo.run();
}
