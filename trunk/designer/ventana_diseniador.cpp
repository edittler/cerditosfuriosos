#include "ventana_diseniador.h"
#include <gdkmm/color.h>

VentanaDiseniador::VentanaDiseniador() {
	set_title("Creador de niveles");
	set_border_width(10);
	set_resizable(false);
	
	listaObjetivos.push_back(Gtk::TargetEntry("POSICIONABLE"));
	
	lienzo.set_size_request(500, 300);
	lienzo.drag_dest_set(listaObjetivos);
	
	paletaEscenario.itemCerdo.drag_source_set(listaObjetivos);
	paletaEscenario.itemHuevos.drag_source_set(listaObjetivos);
	paletaEscenario.itemCajaMadera.drag_source_set(listaObjetivos);
	paletaEscenario.itemCajaMetal.drag_source_set(listaObjetivos);
	
	caja.pack_start(paletaEscenario);
	caja.pack_start(lienzo);
		
	add(caja);
	show_all_children();
}

VentanaDiseniador::~VentanaDiseniador() {}

