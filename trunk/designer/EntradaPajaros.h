#ifndef _PALETA_ENTRADA_PAJAROS_H_
#define _PALETA_ENTRADA_PAJAROS_H_

// C++ Library Includes.
#include <string>

// GTK+ Library Includes.
#include <gtkmm/frame.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/spinbutton.h>

// Common Project Includes.
#include "XMLTypes.h"

// Designer Project Includes.
#include "ConstantesDiseniador.h"

/**
 * Proporciona un panel en el cual se pueden seleccionar las caracteristicas de
 * la entrada de los pajaros enemigos.
 */
class EntradaPajaros : public Gtk::Frame {
public:

	/**
	 * Constructor.
	 * @param anchoEscenario ancho del escenario en pixeles
	 * @param altoEscenario ancho del escenario en pixeles
	 */
	EntradaPajaros(float anchoEscenario, float altoEscenario);

	/**
	 * Destructor.
	 */
	virtual ~EntradaPajaros();

	/**
	 * @return true si la linea de entrada para los pajaros es valida y
	 * false en el caso contrario
	 */
	bool lineaEntradaValida() const;

	/**
	 * @return true si los porcentajes de aparicion de los pajaros suma 100
	 * y false en el caso contrario
	 */
	bool porcentajesPajarosValidos() const;

	/**
	 * @return coordenada y inicial de la linea de entrada de pajaros
	 */
	float getYInicioLineaEntrada() const;

	/**
	 * @return coordenada y final de la linea de entrada de pajaros
	 */
	float getYFinalLineaEntrada() const;

	/**
	 * @return tiempo de generacion de los pajaros
	 */
	int getTiempoGeneracion() const;

	/**
	 * @return probabilidad de generacion de los pajaros
	 */
	int getProbabilidadGeneracion() const;

	/**
	 * @return probabilidad del pajaro rojo
	 */
	int getProbabilidadPajaroRojo() const;

	/**
	 * @return probabilidad del pajaro verde
	 */
	int getProbabilidadPajaroVerde() const;

	/**
	 * @return probabilidad del pajaro azul
	 */
	int getProbabilidadPajaroAzul() const;

	/**
	 * Se cargaran los valores que se habian seleccionado en un nivel ya
	 * existente.
	 * @param rutaNivel ruta del archivo xml que contiene al nivel
	 */
	void cargarNivel(const std::string rutaNivel);

	/**
	 * Se guardaran los valores seleccionados en el archivo del nivel que
	 * se esta editando.
	 * @param rutaNivel ruta del archivo xml que contiene al nivel
	 */
	void guardarNivel(const std::string rutaNivel) const;

private:
	XMLNode* XMLSerializarProbabilidadesPajaros() const;

	float xLineaEntrada;

	Gtk::SpinButton* yInicial;
	Gtk::SpinButton* yFinal;

	Gtk::SpinButton* tiempoGeneracion;

	Gtk::SpinButton* probabilidadGeneracion;

	Gtk::SpinButton* probabilidadRojo;
	Gtk::SpinButton* probabilidadVerde;
	Gtk::SpinButton* probabilidadAzul;
};

#endif
