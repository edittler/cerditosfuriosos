#include "PaletaEscenario.h"

PaletaEscenario::PaletaEscenario():
	itemsJugador("ITEMS JUGADOR"),
	itemsVarios("ITEMS VARIOS"),
	cajaGrupos(false, 0),
	cajaItemsJugador(false, 0),
	cajaItemsVarios(false, 0)
{
	listaObjetivos.push_back(Gtk::TargetEntry("POSICIONABLE"));
	set_border_width(6);
	itemCerdo.signal_drag_data_get().connect(sigc::mem_fun(*this,
								&PaletaEscenario::boton_cerdo_arrastrado));
	itemHuevos.signal_drag_data_get().connect(sigc::mem_fun(*this,
								&PaletaEscenario::boton_huevos_arrastrado));
	itemCajaMadera.signal_drag_data_get().connect(sigc::mem_fun(*this,
								&PaletaEscenario::boton_caja_madera_arrastrado));
	itemCajaMetal.signal_drag_data_get().connect(sigc::mem_fun(*this,
								&PaletaEscenario::boton_caja_metal_arrastrado));
	itemCajaVidrio.signal_drag_data_get().connect(sigc::mem_fun(*this,
								&PaletaEscenario::boton_caja_vidrio_arrastrado));
	itemCerdo.drag_source_set(listaObjetivos);
	itemHuevos.drag_source_set(listaObjetivos);
	itemCajaMadera.drag_source_set(listaObjetivos);
	itemCajaMetal.drag_source_set(listaObjetivos);
	itemCajaVidrio.drag_source_set(listaObjetivos);
	// Agrego los grupos y los items
	agregarItems();
	show_all_children();
}

void PaletaEscenario::boton_cerdo_arrastrado(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time) {
	selection_data.set(selection_data.get_target(), 8, (const guchar*)"CERDO", 5);
}

void PaletaEscenario::boton_huevos_arrastrado(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time) {
	selection_data.set(selection_data.get_target(), 8, (const guchar*)"HUEVOS", 6);
}

void PaletaEscenario::boton_caja_madera_arrastrado(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time) {
	selection_data.set(selection_data.get_target(), 8, (const guchar*)"CAJA_MADERA", 11);
}

void PaletaEscenario::boton_caja_metal_arrastrado(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time) {
	selection_data.set(selection_data.get_target(), 8, (const guchar*)"CAJA_METAL", 10);
}

void PaletaEscenario::boton_caja_vidrio_arrastrado(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time) {
	selection_data.set(selection_data.get_target(), 8, (const guchar*)"CAJA_VIDRIO", 11);
}

void PaletaEscenario::agregarItems() {
	itemsJugador.add(cajaItemsJugador);
	cajaItemsJugador.pack_start(itemCerdo, Gtk::PACK_EXPAND_PADDING, 10);
	cajaItemsJugador.pack_start(itemHuevos, Gtk::PACK_EXPAND_PADDING, 10);
	itemsVarios.add(cajaItemsVarios);
	cajaItemsVarios.pack_start(itemCajaMadera, Gtk::PACK_EXPAND_PADDING, 10);
	cajaItemsVarios.pack_start(itemCajaMetal, Gtk::PACK_EXPAND_PADDING, 10);
	cajaItemsVarios.pack_start(itemCajaVidrio, Gtk::PACK_EXPAND_PADDING, 10);
	cajaGrupos.pack_start(itemsJugador, Gtk::PACK_SHRINK, 10);
	cajaGrupos.pack_start(itemsVarios, Gtk::PACK_SHRINK, 10);
	itemCerdo.add_pixlabel(RUTA_ITEM_CERDO, "Cerdo");
	itemHuevos.add_pixlabel(RUTA_ITEM_HUEVOS, "Huevos");
	itemCajaMadera.add_pixlabel(RUTA_ITEM_CAJA_MADERA, "Caja de madera");
	itemCajaMetal.add_pixlabel(RUTA_ITEM_CAJA_METAL, "Caja de metal");
	itemCajaVidrio.add_pixlabel(RUTA_ITEM_CAJA_VIDRIO, "Caja de vidrio");
	add(cajaGrupos);
	
}

PaletaEscenario::~PaletaEscenario() {}
