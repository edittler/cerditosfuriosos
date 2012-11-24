#ifndef MOUSELISTENER_H_
#define MOUSELISTENER_H_

#include <gdk/gdkevents.h>
#include <gtkmm/widget.h>

#include "Nivel.h"

class MouseListener {
public:
	MouseListener(Nivel& nivel, float x, float y);
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
	Nivel& nivel;
	float x;
	float y;
};

#endif /* MOUSELISTENER_H_ */
