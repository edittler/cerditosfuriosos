#ifndef _VISTA_CUERPO_H_
#define _VISTA_CUERPO_H_

// Hierarchy Include.
#include "ObservadorCuerpo.h"

// C++ Library Includes.
#include <string>

// GTK+ Library Include.
#include <gtkmm/image.h>

// Forward Declarations.
class VistaEscenario;
class CuerpoAbstracto;

class VistaCuerpo: public ObservadorCuerpo, public Gtk::Image {
public:
	/* @brief Constructor.
	 * @param posicion punto de referencia del objeto en el escenario
	 * @param ruta archivo que contiene a la imagen
	 */
	VistaCuerpo(VistaEscenario* escenario, CuerpoAbstracto* cuerpo, const char* ruta);

	/* Destructor.
	 */
	virtual ~VistaCuerpo();

	void actualizarPosicion(Punto2D posicion);

	void seMurio();

protected:
	/* @brief El modelo del escenario trabaja con valores en punto flotante.
	 * Para dibujar a los objetos es preferible contar con coordenadas
	 * enteras que describan una coleccion de pixeles del mismo. Este
	 * metodo realiza el escalado entre los dos tipos de datos para dicha
	 * discretizacion.
	 * Además, tiene en cuenta el tamaño de la imagen y posiciona la imagen
	 * en el centro de coordenadas.
	 * @param Valor flotante que se desea ajustar.
	 */
	int ajustarValorX(float valorFlotante);
	int ajustarValorY(float valorFlotante);


	/**************
	 * ATTRIBUTES *
	 **************/

	/* Dimensiones de la imagen que representa al cuerpo
	 */
	int ancho;
	int alto;

	/* Posiciones en pixeles del cuerpo
	 */
	int x;
	int y;

	/* Vista del escenario que contiene la vista del cuerpo.
	 * Es necesaria para que la vista cuerpo le diga que lo mueva de posicion.
	 */
	VistaEscenario* escenario;

	/* Cuerpo del modelo del cual corresponde la vista.
	 */
	CuerpoAbstracto* cuerpo;
};

#endif /* _VISTA_CUERPO_H_ */
