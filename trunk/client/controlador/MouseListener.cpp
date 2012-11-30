#include "MouseListener.h"
#include "../vista/modelo/ConstantesVistaModelo.h"

MouseListener::MouseListener(Nivel& nivel, float x, float y) : nivel(nivel) {
	this->x = x;
	this->y = y;
}

MouseListener::~MouseListener() { }

void MouseListener::cargarEventos(Gtk::Widget* container) {
	// setea eventos nuevos.
	container->add_events(Gdk::BUTTON_PRESS_MASK);

	// conecta cada evento con su metodo handler
	senial = container->signal_button_press_event().connect(sigc::mem_fun(*this,
		&MouseListener::onClick));
}

void MouseListener::borrarEventos() {
	if (senial.connected())
		senial.disconnect();
}

bool MouseListener::onClick(GdkEventButton* event) {
	// convierto a valores mundo fisica (Box2D)
	float xf = event->x / AJUSTE_ESCALA_VISTA;
	float yf = nivel.getAlto() - event->y / AJUSTE_ESCALA_VISTA;

	// Calculo velocidades iniciales.
	float Vx = DISPARO_VELOCIDAD_X;
	float t = (xf - x) / Vx;
	float Vy = (yf - y) / t - GRAVEDAD_Y * t / 2;

	nivel.lanzarHuevo(Punto2D(x, y), Velocidad2D(Vx, Vy), 1);
	return true;
}
