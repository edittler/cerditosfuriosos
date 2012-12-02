#ifndef _VENTANA_DISENIADOR_H_
#define _VENTANA_DISENIADOR_H_

#include <gtkmm/window.h>
#include <gtkmm/eventbox.h>

#include "InterfazSelectora.h"
#include "PanelImagenFondo.h"
#include "PanelInicial.h"
#include "PanelUnJugador.h"
#include "PanelMultijugador.h"
#include "PanelConfiguracion.h"
#include "PanelCrearPartida.h"
#include "PanelUnirsePartida.h"
#include "PanelEsperandoJugadores.h"
#include "PanelRecords.h"
#include "../modelo/VistaEscenario.h"
#include "../../controlador/MouseListener.h"

/**
 * Ventana principal de la aplicacion.
 */
class VentanaPrincipal : public Gtk::Window, public InterfazSelectora {
public:

	/**
	 * Constructor.
	 */
	VentanaPrincipal();

	/**
	 * Destructor.
	 */
	virtual ~VentanaPrincipal();

	void modoUnJugador();
	void modoMultijugador();
	void modoConfiguracion(std::string direccion, unsigned short int puerto);
	void verRecords();
	void volverAMenuPrincipal();
	void modoCrearPartida(std::string nombreMundos);
	void modoUnirsePartida(std::string nombrePartidas);
	void modoEsperandoJugadores();

	void mostrarMenuPrincipal();

	void mostrarDialogo(std::string mensaje);

	/**
	 * El usuario va a jugar a un nivel, carga la vista del escenario.
	 */
	void agregarContenedor(Gtk::Widget& widget);

	void vaciarContenedor();

	/**
	 * Asigna handler de eventos del mouse al contenedor actual
	 * @param implementacion MouseListener de handlers.
	 */
	void setMouseListener(MouseListener* listener);

	PanelInicial* panelInicial;
	PanelUnJugador* panelUnJugador;
	PanelMultijugador* panelMultijugador;
	PanelConfiguracion* panelConfiguracion;
	PanelCrearPartida* panelCrearPartida;
	PanelUnirsePartida* panelUnirsePartida;
	PanelRecords* panelRecords;
	PanelEsperandoJugadores* panelEsperandoJugadores;

private:
	// Contenedor que permite manejar eventos de hijos.
	Gtk::EventBox* contenedor;

};

#endif
