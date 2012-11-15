#ifndef VENTANACLIENTE_H_
#define VENTANACLIENTE_H_

#include <gtkmm/window.h>
#include <gtkmm/eventbox.h>
#include <gtkmm/widget.h>
#include "../controlador/MouseListener.h"

class VentanaCliente: public Gtk::Window {
public:
	VentanaCliente();
	virtual ~VentanaCliente();

	void agregarContenedor(Gtk::Widget& widget);

	/*
	 * @brief Asigna handler de eventos del mouse al contenedor actual
	 * @param implementacion MouseListener de handlers.
	 */
	void setMouseListener(MouseListener* listener);

private:

	// Contenedor que permite manejar eventos de hijos.
	Gtk::EventBox* contenedor;
};

#endif /* VENTANACLIENTE_H_ */
