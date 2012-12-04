#ifndef PANELCONFIGURACION_H_
#define PANELCONFIGURACION_H_

#include <gtkmm/spinbutton.h>

#include "PanelImagenFondo.h"
#include "InterfazSelectora.h"

// Constantes de layout y tamanio del selector de direccion
#define X_ETIQUETA_DIRECCION 75
#define Y_ETIQUETA_DIRECCION 450
#define X_DIRECCION 175
#define Y_DIRECCION 442
#define ANCHO_DIRECCION 225
#define ALTO_DIRECCION 30
#define DIRECCION_DEFAULT "localhost"
// Constantes del selector de puerto
#define X_ETIQUETA_PUERTO 75
#define Y_ETIQUETA_PUERTO 500
#define X_PUERTO 175
#define Y_PUERTO 496
#define PUERTO_VALOR_DEFAULT 5555
#define PUERTO_MINIMO 1024
#define PUERTO_MAXIMO 65535
// Constantes de layout y tamanio del boton guardar
#define X_BOTON_GUARGAR_CONFIGURACION 450
#define Y_BOTON_GUARGAR_CONFIGURACION 470
#define ANCHO_BOTON_GUARGAR_CONFIGURACION 100
#define ALTO_BOTON_GUARGAR_CONFIGURACION 50
// Constantes de layout del boton volver
#define X_BOTON_VOLVER_CONFIGURACION 25
#define Y_BOTON_VOLVER_CONFIGURACION 550

class PanelConfiguracion: public PanelImagenFondo {
public:
	/**
	 * Constructor
	 */
	PanelConfiguracion(int ancho, int alto, string ruta,
			InterfazSelectora* interfaz);

	/**
	 * Destructor
	 */
	virtual ~PanelConfiguracion();

	/**
	 * Se setean los valores que contienen los campos del panel
	 */
	void setearValores(const std::string direccion,
			const unsigned short int puerto);

	/**
	 * Retorna el valor contenido en el campo Direccion IP
	 */
	std::string getDireccion() const;

	/**
	 * Retorna el valor contenido en el campo Puerto
	 */
	unsigned short int getPuerto() const;

	Gtk::Button* botonGuardar;

private:
	/**
	 * Inicializa los componentes del panel panel
	 */
	void inicializarComponentes();

	/**
	 * El usuario indico que desea volver al menu multijugador.
	 */
	void botonVolverClickeado();

	InterfazSelectora* interfaz;

	Gtk::Entry* direccion;
	Gtk::SpinButton* puerto;

	Gtk::Button* botonVolver;
};

#endif /* PANELCONFIGURACION_H_ */
