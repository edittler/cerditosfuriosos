#ifndef _SELECTOR_IMAGEN_FONDO_H_
#define _SELECTOR_IMAGEN_FONDO_H_

#include <gtkmm/filechooserdialog.h>
#include <gtkmm/filefilter.h>
#include <gtkmm/stock.h>

#include "ConstantesDiseniador.h"

/**
 * Abre un dialogo selector de imagenes que obliga a que la carpeta de la cual
 * se seleccione la imagen en cuestion sea la de fondos.
 */
class SelectorImagenFondo : public Gtk::FileChooserDialog {
public:

	SelectorImagenFondo();
	
	virtual ~SelectorImagenFondo();
	
	void cargarComponentes();
	
	/**
	 * @return nombre del archivo seleccionado, sin la ruta
	 */
	std::string getNombreArchivo();
	
	/**
	 * Senial para manejar el cambio de carpeta.
	 */
	void carpetaCambiada();
};

#endif
