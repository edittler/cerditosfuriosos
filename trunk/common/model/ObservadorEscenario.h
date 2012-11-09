#ifndef OBSERVADORESCENARIO_H_
#define OBSERVADORESCENARIO_H_

// C++ Library Includes
#include <string>

// Superficies Includes.
#include "CajaVidrio.h"
#include "CajaMadera.h"
#include "CajaMetal.h"

// Frutas Includes.
#include "Manzana.h"
#include "Banana.h"
#include "Cereza.h"

// Pajaros Include.
#include "PajaroRojo.h"
#include "PajaroVerde.h"
#include "PajaroAzul.h"

// Disparos Include.
#include "HuevoBlanco.h"
#include "HuevoCodorniz.h"
#include "HuevoPoche.h"
#include "HuevoReloj.h"

// Other Objects Includes.
#include "Cerdito.h"
#include "Catapulta.h"
#include "Monticulo.h"

/* @class ObservadorEscenario
 * Interfaz de observador del escenario que recibe notificaciones del escenario
 * en el cual se registro.
 */
class ObservadorEscenario {
public:
	// Constructor por defecto
	ObservadorEscenario();

	// Destructor
	virtual ~ObservadorEscenario();

	virtual void seAgregoCerdito(Cerdito* cerdito) = 0;

	virtual void seAgregoCatapulta(Catapulta* catapulta) = 0;

	virtual void seAgregoMonticulo(Monticulo* monticulo) = 0;

	virtual void seAgregoCajaVidrio(CajaVidrio* caja) = 0;

	virtual void seAgregoCajaMadera(CajaMadera* caja) = 0;

	virtual void seAgregoCajaMetal(CajaMetal* caja) = 0;

	virtual void seAgregoManzana(Manzana* manzana) = 0;

	virtual void seAgregoBanana(Banana* banana) = 0;

	virtual void seAgregoCereza(Cereza* cereza) = 0;

	virtual void seLanzoPajaroRojo(PajaroRojo* pajaro) = 0;

	virtual void seLanzoPajaroVerde(PajaroVerde* pajaro) = 0;

	virtual void seLanzoPajaroAzul(PajaroAzul* pajaro) = 0;

	virtual void seLanzoHuevoBlanco(HuevoBlanco* huevo) = 0;

	virtual void seLanzoHuevoCodorniz(HuevoCodorniz* huevo) = 0;

	virtual void seLanzoHuevoPoche(HuevoPoche* huevo) = 0;

	virtual void seLanzoHuevoReloj(HuevoReloj* huevo) = 0;

	virtual void monticuloDestruido() = 0;

	/* @brief Será usado en el caso de que el escenario tenga un único cerdito.
	 */
	virtual void cerditoMatado() = 0;

	/* @brief Será usado en el caso multijugador, donde el escenario tiene
	 * varios cerditos.
	 * @param El nombre del jugador al que corresponde el cerdito matado.
	 */
	virtual void cerditoMatado(unsigned int idJugador) = 0;

	virtual void partidaGanada() = 0;

	virtual void partidaPerdida() = 0;
};

#endif  /* OBSERVADORESCENARIO_H_ */
