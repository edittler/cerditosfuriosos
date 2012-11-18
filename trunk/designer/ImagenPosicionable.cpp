#include "ImagenPosicionable.h"

int ImagenPosicionable::contadorInstancias = 0;

ImagenPosicionable::ImagenPosicionable(const char* ruta): Gtk::EventBox() {
	if (contadorInstancias == 0)
		id += '0';
	else {
		int auxiliar = contadorInstancias;
		while (auxiliar > 0) {
			id.insert(0, 1, (char)((auxiliar % 10) + '0'));
			auxiliar = auxiliar / 10;
		}
	}
	++contadorInstancias;
	contenedorFondo = manage(new Gtk::Fixed());
	add(*contenedorFondo);
	set_events(Gdk::ALL_EVENTS_MASK);
	std::list<Gtk::TargetEntry> listaObjetivos;
	listaObjetivos.push_back(Gtk::TargetEntry("POSICIONABLE"));
	drag_source_set(listaObjetivos);
	signal_drag_data_get().connect(sigc::mem_fun(*this,
								&ImagenPosicionable::imagen_arrastrada));
}

std::string ImagenPosicionable::getId() {
	return id;
}

ImagenPosicionable::~ImagenPosicionable() {}

void ImagenPosicionable::imagen_arrastrada(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time) {
	selection_data.set(selection_data.get_target(), 8, (const guchar*)id.c_str(), id.length());
}

int ImagenPosicionable::getX() {
	return x;
}

int ImagenPosicionable::getY() {
	return y;
}

void ImagenPosicionable::setX(int x) {
	this->x = x;
}
		
void ImagenPosicionable::setY(int y) {
	this->y = y;
}

void ImagenPosicionable::setFondo(const Glib::RefPtr< Gdk::Pixbuf >& fondo) {
	Gtk::Image* imagenConFondo = manage(new Gtk::Image(fondo));
	std::vector<Widget*> hijos = contenedorFondo->get_children();
	if (hijos.size() == 2) {
		contenedorFondo->remove(*hijos[0]);
		contenedorFondo->remove(*hijos[1]);
	}
	contenedorFondo->put(*imagenConFondo, 0, 0);
	contenedorFondo->put(*imagenFija, 0, 0);
	contenedorFondo->show_all();
}

float ImagenPosicionable::getXFlotante() {
	return (x+(((float)ancho) / 2))/PIXELES_SOBRE_METRO;
}

float ImagenPosicionable::getYFlotante(int alto) {
	return (alto-(y+(((float)this->alto) / 2)))/PIXELES_SOBRE_METRO;
}
