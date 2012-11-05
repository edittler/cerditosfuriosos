#ifndef _VISTA_CUERPO_H_
#define _VISTA_CUERPO_H_

// Hierarchy Include.
#include "ObservadorCuerpo.h"

// GTK+ Library Include.
#include <gtkmm/image.h>

// Forward Declarations.
class VistaEscenario;

class VistaCuerpo: public ObservadorCuerpo, public Gtk::Image {
public:
	/* @brief Constructor.
	 * @param posicion punto de referencia del objeto en el escenario
	 * @param ruta archivo que contiene a la imagen
	 */
	VistaCuerpo(VistaEscenario* escenario, Punto2D posicion, const char* ruta);

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
	 * @param Valor flotante que se desea ajustar.
	 */
	static int ajustarValor(float valorFlotante);

	/* Posiciones en pixeles del cuerpo
	 */
	int x;
	int y;

	/* Vista del escenario que contiene la vista del cuerpo.
	 * Es necesaria para que la vista cuerpo le diga que lo mueva de posicion.
	 */
	VistaEscenario* escenario;
};

#endif /* _VISTA_CUERPO_H_ */
