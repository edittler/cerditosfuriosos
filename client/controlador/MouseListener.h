#ifndef MOUSELISTENER_H_
#define MOUSELISTENER_H_

#include <gdk/gdkevents.h>
#include <gtkmm/widget.h>

#include "Nivel.h"

class MouseListener {
public:
	/**
	 * Constructor que recibe un nivel del juego y las posiciones x e y de la
	 * posición desde la cual se va a realizar los disparos.
	 * @param nivel asociado en el cual se va a solicitar el lanzamiento de
	 * disparos.
	 * @param x posición inicial de lanzamiento en el eje x.
	 * @param y posición inicial de lanzamiento en el eje y.
	 */
	MouseListener(Nivel& nivel, float x, float y);

	/**
	 * Destructor
	 */
	virtual ~MouseListener();

	/**
	 * Conecta hander de eventos del listener al container.
	 * @param container al cual se conectaran los handler.
	 */
	void cargarEventos(Gtk::Widget* container);

	/**
	 * Desconecta el handler de eventos del listener.
	 */
	void borrarEventos();

	/**
	 * Maneja el click press.
	 * @param informacion del evento.
	 */
	virtual bool onClick(GdkEventButton* event);

protected:
	// conexion que se obtiene al conectarlo al contenedor
	sigc::connection senial;

	// Nivel asociado al que se le va a pedir lanzar disparos
	Nivel& nivel;

	// Posicion inicial donde se va a lanzar los disparos.
	float x;
	float y;
};

#endif /* MOUSELISTENER_H_ */
