// Header Include.
#include "CreadorNivel.h"

CreadorNivel::CreadorNivel(int idProximoNivel,
		InformableSeleccion* informable) {
	this->idProximoNivel = idProximoNivel;
	this->informable = informable;
	// Widgets sin funcionalidad
	Gtk::Label* etiquetaTamanio = manage(new Gtk::Label(
						"Seleccione el tamaño que tendra el escenario: "));
	Gtk::Label* etiquetaDuracion = manage(new Gtk::Label(
						"Seleccione la duración del nivel (en segundos): "));
	Gtk::Label* etiquetaImagen = manage(new Gtk::Label(
						"Seleccione la imagen de fondo del nivel: "));
	Gtk::Label* etiquetaImagenSuelo = manage(new Gtk::Label(
						"Seleccione la imagen del suelo del nivel: "));
	// Widgets con funcionalidad
	selectorTamanio.append_text("Chico");
	selectorTamanio.append_text("Mediano");
	selectorTamanio.append_text("Grande");
	selectorTamanio.set_active_text("Mediano");
	ajuste = new Gtk::Adjustment(1.0, 15.0, MAXIMA_DURACION_NIVEL);
	selectorDuracion = new Gtk::SpinButton(*ajuste);
	selectorDuracion->set_editable(false);
	archivoImagenFondo = new Gtk::Entry();
	archivoImagenSuelo = new Gtk::Entry();
	archivoImagenFondo->set_editable(false);
	archivoImagenSuelo->set_editable(false);
	botonExaminarFondo = new Gtk::Button("Examinar...");
	botonExaminarSuelo = new Gtk::Button("Examinar...");
	// Contenedores
	Gtk::HBox* cajaHorizontalUno = manage(new Gtk::HBox(false, 20));
	cajaHorizontalUno->pack_start(*etiquetaTamanio);
	cajaHorizontalUno->pack_start(selectorTamanio);
	Gtk::HBox* cajaHorizontalDos = manage(new Gtk::HBox(false, 20));
	cajaHorizontalDos->pack_start(*etiquetaDuracion);
	cajaHorizontalDos->pack_start(*selectorDuracion);
	Gtk::HBox* cajaHorizontalTres = manage(new Gtk::HBox(false, 20));
	cajaHorizontalTres->pack_start(*etiquetaImagen);
	cajaHorizontalTres->pack_start(*botonExaminarFondo);
	Gtk::HBox* cajaHorizontalCuatro = manage(new Gtk::HBox(false, 20));
	cajaHorizontalCuatro->pack_start(*etiquetaImagenSuelo);
	cajaHorizontalCuatro->pack_start(*botonExaminarSuelo);
	Gtk::VBox* cajaVerticalAuxiliar = manage(new Gtk::VBox(false, 20));
	cajaVerticalAuxiliar->pack_start(*cajaHorizontalTres);
	cajaVerticalAuxiliar->pack_start(*archivoImagenFondo);
	Gtk::VBox* cajaVerticalAuxiliarDos = manage(new Gtk::VBox(false, 20));
	cajaVerticalAuxiliarDos->pack_start(*cajaHorizontalCuatro);
	cajaVerticalAuxiliarDos->pack_start(*archivoImagenSuelo);
	Gtk::VBox* cajaVertical = manage(new Gtk::VBox(false, 30));
	cajaVertical->pack_start(*cajaHorizontalUno);
	cajaVertical->pack_start(*cajaHorizontalDos);
	cajaVertical->pack_start(*cajaVerticalAuxiliar);
	cajaVertical->pack_start(*cajaVerticalAuxiliarDos);
	add(*cajaVertical);
	// Seniales
	botonExaminarFondo->signal_clicked().connect(sigc::mem_fun(*this,
										&CreadorNivel::botonExaminarClickeado));
	botonExaminarSuelo->signal_clicked().connect(sigc::mem_fun(*this,
								&CreadorNivel::botonExaminarClickeadoSuelo));
}

CreadorNivel::~CreadorNivel() {
	delete ajuste;
	delete selectorDuracion;
	delete archivoImagenFondo;
	delete archivoImagenSuelo;
	delete botonExaminarFondo;
	delete botonExaminarSuelo;
}

void CreadorNivel::botonExaminarClickeado() {
	std::string nombreArchivo = informable->seleccionarImagen();
	archivoImagenFondo->set_text(nombreArchivo);
}

void CreadorNivel::botonExaminarClickeadoSuelo() {
	std::string nombreArchivo = informable->seleccionarImagen();
	archivoImagenSuelo->set_text(nombreArchivo);
}

float CreadorNivel::getAnchoEscenario() {
	if (selectorTamanio.get_active_text().compare("Chico") == 0)
		return ANCHO_ESCENARIO_CHICO;
	if (selectorTamanio.get_active_text().compare("Mediano") == 0)
		return ANCHO_ESCENARIO_MEDIANO;
	return ANCHO_ESCENARIO_GRANDE;
}
		
float CreadorNivel::getAltoEscenario() {
	if (selectorTamanio.get_active_text().compare("Chico") == 0)
		return ALTO_ESCENARIO_CHICO;
	if (selectorTamanio.get_active_text().compare("Mediano") == 0)
		return ALTO_ESCENARIO_MEDIANO;
	return ALTO_ESCENARIO_GRANDE;
}

int CreadorNivel::getDuracion() {
	return selectorDuracion->get_value_as_int();
}
		
std::string CreadorNivel::getRutaImagenFondo() {
	return (std::string(RUTA_FONDOS)+=archivoImagenFondo->get_text());
}

std::string CreadorNivel::getRutaImagenSuelo() {
	return (std::string(RUTA_FONDOS)+=archivoImagenSuelo->get_text());
}

bool CreadorNivel::imagenFondoSeleccionada() {
	return (archivoImagenFondo->get_text().size() != 0);
}

bool CreadorNivel::imagenSueloSeleccionada() {
	return (archivoImagenSuelo->get_text().size() != 0);
}
