#ifndef _VENTANA_DISENIADOR_H_
#define _VENTANA_DISENIADOR_H_

#include <gtkmm/window.h>
#include <gtkmm/eventbox.h>

#include "PanelInicial.h"
#include "PanelUnJugador.h"
#include "PanelMultijugador.h"
#include "PanelUnirsePartida.h"
#include "PanelRecords.h"
#include "PanelCrearPartida.h"
#include "InterfazSelectora.h"
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

	virtual void modoUnJugador();
	virtual void volverAMenuPrincipal();
	virtual void modoMultijugador();
	virtual void unirseAPartida();
	virtual void verRecords();
	virtual void modoCrearPartida(std::string nombreMundos);

	void mostrarDialogo(std::string mensaje);

	/**
	 * El usuario va a jugar a un nivel, carga la vista del escenario.
	 */
	void agregarContenedor(Gtk::Widget& widget);

	/**
	 * Asigna handler de eventos del mouse al contenedor actual
	 * @param implementacion MouseListener de handlers.
	 */
	void setMouseListener(MouseListener* listener);

	PanelInicial* panelInicial;
	PanelUnJugador* panelUnJugador;
	PanelMultijugador* panelMultijugador;
	PanelUnirsePartida* panelUnirsePartida;
	PanelRecords* panelRecords;
	PanelCrearPartida* panelCrearPartida;

private:

	// Contenedor que permite manejar eventos de hijos.
	Gtk::EventBox* contenedor;

};

#endif
