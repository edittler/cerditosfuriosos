#include "lienzo.h"

Lienzo::Lienzo() {
	this->signal_drag_data_received().connect(sigc::mem_fun(*this,
              &Lienzo::on_label_drop_drag_data_received));
}

Lienzo::~Lienzo() {}

void Lienzo::on_label_drop_drag_data_received(
								const Glib::RefPtr<Gdk::DragContext>& context,
								int x,
								int y,
								const Gtk::SelectionData& selection_data,
								guint info,
								guint time) {
	/*const int length = selection_data.get_length();
	if((length >= 0) && (selection_data.get_format() == 8))
	{
		std::cout << "Received \"" << selection_data.get_data()
		<< "\" in label " << std::endl;
		std::cout << x << std::endl;
		std::cout << y << std::endl;
	}*/
	ImagenPosicionable* imagen;
	std::string recepcion = selection_data.get_data_as_string();
	if (recepcion.compare("CERDO") == 0)
		imagen = manage(new ImagenPosicionable(RUTA_CERDO, x, y));
	else {
		if (recepcion.compare("HUEVOS") == 0)
			imagen = manage(new ImagenPosicionable(RUTA_HUEVOS, x, y));
		else {
			if (recepcion.compare("CAJA_MADERA") == 0)
				imagen = manage(new ImagenPosicionable(RUTA_CAJA_MADERA, x, y));
			else {
				imagen = manage(new ImagenPosicionable(RUTA_CAJA_METAL, x, y));
			}
		}
	}
	put(*imagen, x, y);
	show_all();
}
