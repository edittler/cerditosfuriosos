#include "MouseListener.h"
#include "../vista/modelo/ConstantesVistaModelo.h"

MouseListener::MouseListener(Escenario* escenario) {
	this->escenario = escenario;
}

MouseListener::~MouseListener() { }

void MouseListener::cargarEventos(Gtk::Widget* container) {
	// setea eventos nuevos, eliminando eventos registrados previamente.
	container->set_events(Gdk::BUTTON_PRESS_MASK);

	// conecta cada evento con su metodo handler
	container->signal_button_press_event().connect(sigc::mem_fun(*this,
		&MouseListener::onClick));
}

bool MouseListener::onClick(GdkEventButton* event) {
	// convierto a valores mundo fisica (Box2D)
	float xf = event->x / AJUSTE_ESCALA_VISTA;
	float yf = escenario->getAlto() - event->y / AJUSTE_ESCALA_VISTA;

	float x0 = 1, y0 = 1;  // FIXME se tiene que tomar posicion de la catapulta

	// Calculo velocidades iniciales.
	float Vx = DISPARO_VELOCIDAD_X;
	float t = (xf - x0) / Vx;
	float Vy = (yf - y0) / t - GRAVEDAD_Y * t / 2;

	escenario->lanzarHuevo(Punto2D(x0, y0), Velocidad2D(Vx, Vy));
	return true;
}
