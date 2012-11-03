#include "Lienzo.h"
#include <iostream>

Lienzo::Lienzo() {
	this->signal_drag_data_received().connect(sigc::mem_fun(*this,
              &Lienzo::recibirInformacion));
}

Lienzo::~Lienzo() {}

void Lienzo::recibirInformacion(
								const Glib::RefPtr<Gdk::DragContext>& context,
								int x,
								int y,
								const Gtk::SelectionData& selection_data,
								guint info,
								guint time) {
	ImagenPosicionable* imagen;
	std::string recepcion = selection_data.get_data_as_string();
	if (recepcion.compare("CERDO") == 0)
		imagen = manage(new ImagenCerdo(x, y));
	else {
		if (recepcion.compare("HUEVOS") == 0)
			imagen = manage(new ImagenHuevos(x, y));
		else {
			if (recepcion.compare("CAJA_MADERA") == 0)
				imagen = manage(new ImagenCajaMadera(x, y));
			else {
				if (recepcion.compare("CAJA_METAL") == 0)
					imagen = manage(new ImagenCajaMetal(x, y));
				else {
					if (recepcion.compare("CAJA_VIDRIO") == 0)
						imagen = manage(new ImagenCajaVidrio(x, y));
					else {
						list<ImagenPosicionable*>::iterator iterador =
														posicionables.begin();
						while (iterador != posicionables.end()) {
							if ((*iterador)->getId().compare(recepcion) == 0) {
								move(*(*iterador), x, y);
								break;
							}
							++iterador;
						}
						return;
					}
				}
			}
		}
	}
	posicionables.push_front(imagen);
	put(*imagen, x, y);
	show_all();
}
