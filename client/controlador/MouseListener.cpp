#include "MouseListener.h"
#include "../vista/modelo/ConstantesVistaModelo.h"

MouseListener::MouseListener(Nivel& nivel) : nivel(nivel) { }

MouseListener::~MouseListener() { }

void MouseListener::cargarEventos(Gtk::Widget* container) {
	// setea eventos nuevos.
	container->add_events(Gdk::BUTTON_PRESS_MASK);

	// conecta cada evento con su metodo handler
	container->signal_button_press_event().connect(sigc::mem_fun(*this,
		&MouseListener::onClick));
}

bool MouseListener::onClick(GdkEventButton* event) {
	// convierto a valores mundo fisica (Box2D)
	float xf = event->x / AJUSTE_ESCALA_VISTA;
	float yf = nivel.getAlto() - event->y / AJUSTE_ESCALA_VISTA;

	float x0 = 1.3, y0 = 1.3;  // FIXME se tiene que tomar posicion de la catapulta

	// Calculo velocidades iniciales.
	float Vx = DISPARO_VELOCIDAD_X;
	float t = (xf - x0) / Vx;
	float Vy = (yf - y0) / t - GRAVEDAD_Y * t / 2;

	nivel.lanzarHuevo(Punto2D(x0, y0), Velocidad2D(Vx, Vy), 1);
	return true;
}
