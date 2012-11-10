#ifndef MOUSELISTENER_H_
#define MOUSELISTENER_H_

#include <gdk/gdkevents.h>
#include <gtkmm/widget.h>

#include "Escenario.h"
#include "Jugador.h"

class MouseListener {
public:
	MouseListener(Escenario* escenario, Jugador* jugador);
	virtual ~MouseListener();

	/*
	 * @brief Conecta hander de eventos del listener al container.
	 * @param container al cual se conectaran los handler.
	 */
	void cargarEventos(Gtk::Widget* container);

	/*
	 * @brief Maneja el click press.
	 * @param informacion del evento.
	 */
	virtual bool onClick(GdkEventButton* event);

protected:
	Escenario* escenario;
	Jugador* jugador;
};

#endif /* MOUSELISTENER_H_ */
