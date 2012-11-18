#include "PanelEscenario.h"

PanelEscenario::PanelEscenario(string rutaNivel,
								InformableSeleccion* informable,
								int cantidadJugadores,
								bool nivelNuevo) {
	this->cantidadJugadores = cantidadJugadores;
	this->rutaNivel = rutaNivel;
	this->informable = informable;
	cargarCaracteristicasNivel();
	int ancho = (int)(anchoFlotante * PIXELES_SOBRE_METRO);
	int alto = (int)(altoFlotante * PIXELES_SOBRE_METRO);
	// Inicializacion de los widgets propios
	lienzo = new Lienzo(ancho, alto, cantidadJugadores, rutaFondo, informable);
	paletaEscenario = new PaletaEscenario();
	eliminador = new EliminadorPosicionables(lienzo);
	entrada = new EntradaPajaros(anchoFlotante, altoFlotante);
	if (!nivelNuevo) {
		lienzo->cargarNivel(rutaNivel);
		entrada->cargarNivel(rutaNivel);
	}
	// Inicializacion del boton para guardar el nivel
	botonGuardar = new Gtk::Button();
	Gtk::Image* imagenGuardar = manage(new Gtk::Image(
			Gtk::StockID("gtk-floppy"), Gtk::IconSize(Gtk::ICON_SIZE_BUTTON)));
	botonGuardar->set_image(*imagenGuardar);
	Gtk::Label* etiquetaGuardar = manage(new Gtk::Label("Guardar nivel: "));
	// Contenedores
	Gtk::VBox* cajaVerticalUno = manage(new Gtk::VBox(false, 20));
	cajaVerticalUno->pack_start(*paletaEscenario);
	cajaVerticalUno->pack_start(*eliminador);
	Gtk::HButtonBox* cajaAuxiliarUno = manage(new Gtk::HButtonBox());
	cajaAuxiliarUno->set_layout(Gtk::BUTTONBOX_CENTER);
	cajaAuxiliarUno->pack_start(*botonGuardar, Gtk::PACK_SHRINK);
	Gtk::HBox* cajaHorizontalUno = manage(new Gtk::HBox(false, 20));
	cajaHorizontalUno->pack_start(*etiquetaGuardar);
	cajaHorizontalUno->pack_start(*cajaAuxiliarUno);
	Gtk::VBox* cajaVerticalDos = manage(new Gtk::VBox(false, 20));
	cajaVerticalDos->pack_start(*entrada);
	cajaVerticalDos->pack_start(*cajaHorizontalUno);
	Gtk::HBox* cajaHorizontal = manage(new Gtk::HBox(false, 20));
	cajaHorizontal->pack_start(*cajaVerticalUno);
	cajaHorizontal->pack_start(*lienzo);
	cajaHorizontal->pack_start(*cajaVerticalDos);
	add(*cajaHorizontal);
	// Seniales
	botonGuardar->signal_clicked().connect(sigc::mem_fun(*this,
									&PanelEscenario::botonGuardarClickeado));
}

PanelEscenario::~PanelEscenario() {
	delete paletaEscenario;
	delete lienzo;
	delete eliminador;
	delete entrada;
	delete botonGuardar;
}

void PanelEscenario::botonGuardarClickeado() {
	bool escenarioValido = true;
	std::string mensaje("Antes de poder guardar debe realizar las siguientes correciones:\n");
	if (!(entrada->lineaEntradaValida())) {
		escenarioValido = false;
		mensaje += "- La línea de entrada de pajaros no tiene puntos de inicio y fin válidos\n";
	}
	if (!(entrada->porcentajesPajarosValidos())) {
		escenarioValido = false;
		mensaje += "- Los porcentajes de aparición de los pájaros no suman 100%\n";
	}
	if (!(lienzo->cantidadJugadoresValida())) {
		escenarioValido = false;
		mensaje += "- El numero de jugadores debe ser ";
		mensaje += (char)(cantidadJugadores + '0');
		mensaje += "\n";
	}
	if (!(lienzo->objetosJugadoresCorrectos())) {
		escenarioValido = false;
		mensaje += "- Debe haber una catapulta y un montículo por cada cerdo\n";
	}
	if (!escenarioValido) {
		informable->mostrarDialogo(mensaje);
		return;
	}
	lienzo->guardarNivel(rutaNivel);
	entrada->guardarNivel(rutaNivel);
}

void PanelEscenario::cargarCaracteristicasNivel() {
	/* 
	 * Informacion para Eze:
	 * 
	 * Aca deben cargarse en los atributos correspondientes las caracteristicas
	 * propias del nivel.
	 * 
	 * Para esto contas con el atributo "rutaNivel" que tiene la ruta del archivo
	 * xml que contiene al nivel en cuestion.
	 * 
	 * En el siguiente ejemplo se ve cuales son estas caracteristicas:
	 */
	anchoFlotante = 12;
	altoFlotante = 9;
	rutaFondo = "../common/images/scene/Bosque.png";
}
