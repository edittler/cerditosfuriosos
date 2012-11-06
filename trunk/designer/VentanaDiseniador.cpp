#include "VentanaDiseniador.h"
#include <gdkmm/color.h>

VentanaDiseniador::VentanaDiseniador() {
	set_title("Creador de niveles");
	set_border_width(10);
	set_resizable(false);
	
	/* */
	lienzo = new Lienzo(800, 600);
	/* */
	paletaEscenario = new PaletaEscenario();
	cajaPaletaBorrar.pack_start(*paletaEscenario);
	/* */
	eliminador = new EliminadorPosicionables(lienzo);
	cajaPaletaBorrar.pack_start(*eliminador);
	/* */
	caja.pack_start(cajaPaletaBorrar);
	caja.pack_start(*lienzo);
	/* */
	add(caja);
	show_all_children();
}

VentanaDiseniador::~VentanaDiseniador() {
	delete paletaEscenario;
	delete lienzo;
	delete eliminador;
}

