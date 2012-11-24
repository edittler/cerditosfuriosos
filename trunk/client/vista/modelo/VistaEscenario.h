#ifndef _VISTA_ESCENARIO_H_
#define _VISTA_ESCENARIO_H_

// Hierarchy Include.
#include "../../../common/model/ObservadorEscenario.h"

//C++ Library Includes.
#include <list>

// GTK+ Library Includes.
#include <gtkmm/fixed.h>
#include <gtkmm/image.h>

// Project Includes.
#include "Escenario.h"

// Forward Declarations.
class VistaCuerpo;

class VistaEscenario: public ObservadorEscenario, public Gtk::Fixed {
public:

	explicit VistaEscenario(Escenario* escenario);

	virtual ~VistaEscenario();

	void cargarEscenario();

	/**
	 * Mueve un widget contenido en este contenedor hacia la nueva posicion
	 * indicada.
	 * @param cuerpo widget que queremos mover
	 * @param x abscisa de la nueva posicion
	 * @param y ordenada de la nueva posicion
	 */
	void mover(VistaCuerpo* cuerpo, int x, int y);
	
	/**
	 * Deja de mostrar un widget contenido en este contenedor.
	 * @param cuerpo widget que queremos dejar de mostrar
	 */
	void eliminar(VistaCuerpo* cuerpo);

	void seAjustoTamanio(float ancho, float alto);

	void seEstablecioFondo();

	void seEstablecioSuelo();

	void seAgregoCerdito(Cerdito* cerdito);

	void seAgregoCatapulta(Catapulta* catapulta);

	void seAgregoMonticulo(Monticulo* monticulo);

	void seAgregoCajaVidrio(CajaVidrio* caja);

	void seAgregoCajaMadera(CajaMadera* caja);

	void seAgregoCajaMetal(CajaMetal* caja);

	void seAgregoManzana(Manzana* manzana);

	void seAgregoBanana(Banana* banana);

	void seAgregoCereza(Cereza* cereza);

	void seLanzoPajaroRojo(PajaroRojo* pajaro);

	void seLanzoPajaroVerde(PajaroVerde* pajaro);

	void seLanzoPajaroAzul(PajaroAzul* pajaro);

	void seLanzoHuevoBlanco(HuevoBlanco* huevo);

	void seLanzoHuevoCodorniz(HuevoCodorniz* huevo);

	void seLanzoHuevoPoche(HuevoPoche* huevo);

	void seLanzoHuevoReloj(HuevoReloj* huevo);

	void monticuloDestruido();

	/* @brief Será usado en el caso de que el escenario tenga un único cerdito.
	 */
	void cerditoMatado();

	/* @brief Será usado en el caso multijugador, donde el escenario tiene
	 * varios cerditos.
	 * @param El id del jugador al que corresponde el cerdito matado.
	 */
	void cerditoMatado(unsigned int idJugador);

	void partidaGanada();

	void partidaPerdida();

	int getAncho() const;
	int getAlto() const;

private:


	/*
	 * @brief carga y escala la imagen correspondiente al fondo
	 */
	void iniciarImagenFondo();

	/*
	 * @brief carga y escala la imagen correspondiente al suelo
	 */
	void iniciarImagenSuelo();

	/**************
	 * ATTRIBUTES *
	 **************/

	/* Escenario del modelo */
	Escenario* escenario;

	/* Dimensiones de la vista del escenario */
	int ancho;
	int alto;

	/* Lista de Vista de cuerpos */
	std::list<VistaCuerpo*> vCuerpos;

	/* Imagen de fondo */
	Gtk::Image* fondo;

	/* Imagen de suelo */
	Gtk::Image* suelo;
};

#endif  /* _VISTA_ESCENARIO_H_ */
