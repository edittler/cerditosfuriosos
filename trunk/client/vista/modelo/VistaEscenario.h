#ifndef _VISTA_ESCENARIO_H_
#define _VISTA_ESCENARIO_H_

// Hierarchy Include.
#include "ObservadorEscenario.h"

// Forward Declarations.
class VistaCuerpo;

class VistaEscenario: public ObservadorEscenario {
public:

	VistaEscenario();

	virtual ~VistaEscenario();

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
	 * @param El nombre del jugador al que corresponde el cerdito matado.
	 */
	void cerditoMatado(std::string nombreJugador);

	void partidaGanada();
};

#endif  /* _VISTA_ESCENARIO_H_ */
