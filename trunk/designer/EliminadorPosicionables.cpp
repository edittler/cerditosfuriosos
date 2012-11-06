#include "EliminadorPosicionables.h"

EliminadorPosicionables::EliminadorPosicionables(Lienzo* lienzo) {
	this->lienzo = lienzo;
	Gtk::Image* imagen = manage(new Gtk::Image(Gtk::StockID("gtk-delete"),
								Gtk::IconSize(Gtk::ICON_SIZE_BUTTON)));
	Gtk::Label* etiqueta = manage(new Gtk::Label("Arrastre para eliminar"));
	caja.pack_start(*imagen);
	caja.pack_start(*etiqueta);
	add(caja);
	listaObjetivos.push_back(Gtk::TargetEntry("POSICIONABLE"));
	drag_dest_set(listaObjetivos);
	this->signal_drag_data_received().connect(sigc::mem_fun(*this,
		&EliminadorPosicionables::recibirInformacion));
}

EliminadorPosicionables::~EliminadorPosicionables() {}

void EliminadorPosicionables::recibirInformacion(
								const Glib::RefPtr<Gdk::DragContext>& context,
								int x,
								int y,
								const Gtk::SelectionData& selection_data,
								guint info,
								guint time) {
	string recepcion = selection_data.get_data_as_string();
	lienzo->eliminarImagen(recepcion);
}
