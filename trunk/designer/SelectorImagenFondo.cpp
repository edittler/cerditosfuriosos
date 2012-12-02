#include "SelectorImagenFondo.h"

SelectorImagenFondo::SelectorImagenFondo() :
	 Gtk::FileChooserDialog("Seleccione una imagen",
							Gtk::FILE_CHOOSER_ACTION_OPEN)
{
}

SelectorImagenFondo::~SelectorImagenFondo() {}

void SelectorImagenFondo::cargarComponentes() {
	add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
	set_current_folder(RUTA_FONDOS);
	Gtk::FileFilter filtroImagenes;
	filtroImagenes.set_name("Imagenes");
	filtroImagenes.add_mime_type("image/*");
	add_filter(filtroImagenes);
}

std::string SelectorImagenFondo::getNombreArchivo() {
	std::string seleccion = get_filename();
	std::string auxiliar(RUTA_FONDOS);
	int posicion = seleccion.find(auxiliar.substr(2, auxiliar.size()-1));
	// Si la imagen no se encuentra en la carpeta la copia alli
	if (posicion == -1) {		
		std::string rutaNueva(RUTA_FONDOS);
		rutaNueva += seleccion.substr(seleccion.find_last_of('/')+1,
				seleccion.size()-seleccion.find_last_of('/')-1);
		FILE* original = fopen(seleccion.c_str(), "r");
		FILE* copia = fopen(rutaNueva.c_str(), "w");
		fseek(original, 0, SEEK_SET);
		fseek(copia, 0, SEEK_SET);
		while (!(feof(original)))
			fputc(fgetc(original), copia);
		fputc(fgetc(original), copia);
		fclose(original);
		fclose(copia);
	}
	seleccion = seleccion.substr(seleccion.find_last_of('/')+1,
				seleccion.size()-seleccion.find_last_of('/')-1);
	return seleccion;
}

void SelectorImagenFondo::carpetaCambiada() {
	set_current_folder(RUTA_FONDOS);
}
