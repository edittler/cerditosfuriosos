#ifndef _IMAGEN_POSICIONABLE_H_
#define _IMAGEN_POSICIONABLE_H_

// C++ Library Includes.
#include <string>
#include <list>
#include <vector>

// GTK+ Library Includes.
#include <gtkmm/image.h>
#include <gtkmm/eventbox.h>
#include <gtkmm/fixed.h>

// Common Project Includes.
#include "XMLTypes.h"

// Designer Project Includes.
#include "ConstantesDiseniador.h"

/**
 * Las instancias de esta clase representan a imagenes que pueden colocarse en
 * un lienzo a traves de un drag and drop.
 */
class ImagenPosicionable : public Gtk::EventBox {
public:
	/**
	 * Destructor.
	 */
	virtual ~ImagenPosicionable();

	/**
	 * Devuelve un string que identifica univocamente a esta instancia.
	 */
	std::string getId() const;

	/**
	 * @return abscisa de la esquina superior derecha de la imagen
	 */
	int getX() const;

	/**
	 * @return ordenada de la esquina superior derecha de la imagen
	 */
	int getY() const;

	/**
	 * @param x abscisa de la esquina superior derecha de la imagen
	 */
	void setX(const int x);

	/**
	 * @param y ordenada de la esquina superior derecha de la imagen
	 */
	void setY(const int y);

	// Dimensiones de la imagen en pixeles
	int alto;
	int ancho;

	/**
	 * Agrega un fondo a la imagen que sera mostrada.
	 * @param fondo pixeles del fondo
	 */
	void setFondo(const Glib::RefPtr< Gdk::Pixbuf >& fondo);

	/**
	 * @return coordenada x del objeto mostrado por esta imagen dentro del
	 * modelo
	 */
	float getXFlotante() const;

	/**
	 * @param alto altura del escenario en pixeles
	 * @return coordenada y del objeto mostrado por esta imagen dentro del
	 * modelo
	 */
	float getYFlotante(const int altoEscenario) const;

protected:

	/**
	 * Constructor.
	 * @param ruta donde se encuentra el archivo con la imagen
	 */
	explicit ImagenPosicionable(const char* ruta);

	XMLNode* serializarCoordenadas(const int altoEscenario) const;

	/**
	 * Coordenadas del objeto en el lienzo que integra.
	 */
	int x, y;
	
	/**
	 * Imagen que sera mostrada.
	 */
	Gtk::Image* imagenFija;
	
	Gtk::Fixed* contenedorFondo;
	
	/* Un identificador unico para cada instancia de esta clase o una
	 * subclase de la misma. */
	std::string id;
	
	/* Lleva una cuenta de la cantidad de instancias de esta clase (y de sus
	 * subclases) que se crean, para darle a cada una un identificador. */
	static int contadorInstancias;

	void imagen_arrastrada(const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time);
};

#endif
