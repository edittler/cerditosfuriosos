#include "PaletaEscenario.h"

PaletaEscenario::PaletaEscenario():
	itemsJugador("ITEMS JUGADOR"),
	itemsCajas("ITEMS CAJAS"),
	itemsFrutas("ITEMS FRUTAS")
{
	cajaItemsJugador = manage(new Gtk::VBox(false, 0));
	cajaItemsCajas = manage(new Gtk::VBox(false, 0));
	cajaItemsFrutas = manage(new Gtk::VBox(false, 0));
	cajaGrupos = manage(new Gtk::VBox(false, 0));
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
	itemBanana.signal_drag_data_get().connect(sigc::mem_fun(*this,
								&PaletaEscenario::boton_banana_arrastrado));
	itemCereza.signal_drag_data_get().connect(sigc::mem_fun(*this,
								&PaletaEscenario::boton_cereza_arrastrado));
	itemManzana.signal_drag_data_get().connect(sigc::mem_fun(*this,
								&PaletaEscenario::boton_manzana_arrastrado));
	itemCatapulta.signal_drag_data_get().connect(sigc::mem_fun(*this,
								&PaletaEscenario::boton_catapulta_arrastrado));
	itemCerdo.drag_source_set(listaObjetivos);
	itemHuevos.drag_source_set(listaObjetivos);
	itemCajaMadera.drag_source_set(listaObjetivos);
	itemCajaMetal.drag_source_set(listaObjetivos);
	itemCajaVidrio.drag_source_set(listaObjetivos);
	itemBanana.drag_source_set(listaObjetivos);
	itemCereza.drag_source_set(listaObjetivos);
	itemManzana.drag_source_set(listaObjetivos);
	itemCatapulta.drag_source_set(listaObjetivos);
	itemCerdo.drag_source_set_icon(Gtk::Image(RUTA_CERDO).get_pixbuf()->scale_simple(ANCHO_CERDO, ALTO_CERDO, Gdk::INTERP_BILINEAR));
	itemCajaMadera.drag_source_set_icon(Gtk::Image(RUTA_CAJA_MADERA).get_pixbuf()->scale_simple(ANCHO_CAJA_MADERA, ALTO_CAJA_MADERA, Gdk::INTERP_BILINEAR));
	itemCajaMetal.drag_source_set_icon(Gtk::Image(RUTA_CAJA_METAL).get_pixbuf()->scale_simple(ANCHO_CAJA_METAL, ALTO_CAJA_METAL, Gdk::INTERP_BILINEAR));
	itemCajaVidrio.drag_source_set_icon(Gtk::Image(RUTA_CAJA_VIDRIO).get_pixbuf()->scale_simple(ANCHO_CAJA_VIDRIO, ANCHO_CAJA_VIDRIO, Gdk::INTERP_BILINEAR));
	itemHuevos.drag_source_set_icon(Gtk::Image(RUTA_HUEVOS).get_pixbuf()->scale_simple(ANCHO_HUEVOS, ANCHO_HUEVOS, Gdk::INTERP_BILINEAR));
	itemBanana.drag_source_set_icon(Gtk::Image(RUTA_BANANA).get_pixbuf()->scale_simple(ANCHO_BANANA, ANCHO_BANANA, Gdk::INTERP_BILINEAR));
	itemCereza.drag_source_set_icon(Gtk::Image(RUTA_CEREZA).get_pixbuf()->scale_simple(ANCHO_CEREZA, ANCHO_CEREZA, Gdk::INTERP_BILINEAR));
	itemManzana.drag_source_set_icon(Gtk::Image(RUTA_MANZANA).get_pixbuf()->scale_simple(ANCHO_MANZANA, ANCHO_MANZANA, Gdk::INTERP_BILINEAR));
	itemCatapulta.drag_source_set_icon(Gtk::Image(RUTA_CATAPULTA).get_pixbuf()->scale_simple(ANCHO_CATAPULTA, ANCHO_CATAPULTA, Gdk::INTERP_BILINEAR));
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

void PaletaEscenario::boton_catapulta_arrastrado(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time) {
	selection_data.set(selection_data.get_target(), 8, (const guchar*)"CATAPULTA", 9);
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

void PaletaEscenario::boton_banana_arrastrado(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time) {
	selection_data.set(selection_data.get_target(), 8, (const guchar*)"BANANA", 6);
}

void PaletaEscenario::boton_cereza_arrastrado(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time) {
	selection_data.set(selection_data.get_target(), 8, (const guchar*)"CEREZA", 6);
}

void PaletaEscenario::boton_manzana_arrastrado(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time) {
	selection_data.set(selection_data.get_target(), 8, (const guchar*)"MANZANA", 7);
}

void PaletaEscenario::agregarItems() {
	itemsJugador.add(*cajaItemsJugador);
	cajaItemsJugador->pack_start(itemCerdo, Gtk::PACK_EXPAND_PADDING, 3);
	cajaItemsJugador->pack_start(itemHuevos, Gtk::PACK_EXPAND_PADDING, 3);
	cajaItemsJugador->pack_start(itemCatapulta, Gtk::PACK_EXPAND_PADDING, 3);
	itemsCajas.add(*cajaItemsCajas);
	cajaItemsCajas->pack_start(itemCajaMadera, Gtk::PACK_EXPAND_PADDING, 3);
	cajaItemsCajas->pack_start(itemCajaMetal, Gtk::PACK_EXPAND_PADDING, 3);
	cajaItemsCajas->pack_start(itemCajaVidrio, Gtk::PACK_EXPAND_PADDING, 3);
	itemsFrutas.add(*cajaItemsFrutas);
	cajaItemsFrutas->pack_start(itemBanana, Gtk::PACK_EXPAND_PADDING, 3);
	cajaItemsFrutas->pack_start(itemCereza, Gtk::PACK_EXPAND_PADDING, 3);
	cajaItemsFrutas->pack_start(itemManzana, Gtk::PACK_EXPAND_PADDING, 3);
	cajaGrupos->pack_start(itemsJugador, Gtk::PACK_SHRINK, 5);
	cajaGrupos->pack_start(itemsCajas, Gtk::PACK_SHRINK, 5);
	cajaGrupos->pack_start(itemsFrutas, Gtk::PACK_SHRINK, 5);
	itemCerdo.add_pixlabel(RUTA_ITEM_CERDO, "Cerdo");
	itemHuevos.add_pixlabel(RUTA_ITEM_HUEVOS, "Huevos");
	itemCajaMadera.add_pixlabel(RUTA_ITEM_CAJA_MADERA, "Caja de madera");
	itemCajaMetal.add_pixlabel(RUTA_ITEM_CAJA_METAL, "Caja de metal");
	itemCajaVidrio.add_pixlabel(RUTA_ITEM_CAJA_VIDRIO, "Caja de vidrio");
	itemBanana.add_pixlabel(RUTA_ITEM_BANANA, "Banana");
	itemCereza.add_pixlabel(RUTA_ITEM_CEREZA, "Cereza");
	itemManzana.add_pixlabel(RUTA_ITEM_MANZANA, "Manzana");
	itemCatapulta.add_pixlabel(RUTA_ITEM_CATAPULTA, "Catapulta");
	add(*cajaGrupos);
}

PaletaEscenario::~PaletaEscenario() {}
