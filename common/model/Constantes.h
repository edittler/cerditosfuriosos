/* CONSTANTES DE LOS OBJETOS DE LA ESCENA
 * Como la vida de los objetos, los daños que se realizan entre ellos, las
 * dimensiones, restitucion, densidad y otras propiedades.
 *
 * ATENCION: El RADIO de los cuerpos tienen que tener como minimo un valor de
 * 			 0.1f para evitar el efecto tunneling.
 *
 * ATENCION: Si los huevos adquieren mucha velocidad activar propiedad 'bullet'
 *           para evitar tunneling.
 */

#ifndef CONSTANTES_H_
#define CONSTANTES_H_

#include "ConstantesColisiones.h"

// CONSTANTES DE CONFIGURACION
#define VELOCIDAD_ITERACIONES 10
#define POSICION_ITERACIONES 8
#define GRAVEDAD_X 0.0f
#define GRAVEDAD_Y -10.0f

// CONSTANTES DE SUPERFICIES
#define CAJA_MEDIO_ANCHO 0.3f
// CAJA VIDRIO
#define CV_VIDA 1
#define CV_PUNTOS 10
// CAJA MADERA
#define CMA_VIDA 2
#define CMA_PUNTOS 20
// CAJA METAL
#define CME_VIDA 3
#define CME_PUNTOS 30

// CONSTANTES DE PAJAROS
// PAJARO ROJO
#define PR_VIDA 0.5f
#define PR_RADIO 0.2f
#define PR_RESTITUCION 0.33f
#define PR_DANIO_CERDITO 1.0f
#define PR_DANIO_SUPERFICIE 0.5f
// PAJARO VERDE
#define PV_VIDA 1.0f
#define PV_RADIO 0.25f
#define PV_RESTITUCION 0.2f
#define PV_DANIO_CERDITO 2.0f
#define PV_DANIO_SUPERFICIE 1.0f
// PAJARO AZUL
#define PA_VIDA 1.0f
#define PA_RADIO 0.2f
#define PA_RESTITUCION 0.4f
#define PA_DANIO_CERDITO 1.0f
#define PA_DANIO_SUPERFICIE 0.5f

// CONSTANTES DE DISPAROS
#define DISPARO_VELOCIDAD_X 10.0f
// HUEVO BLANCO
#define HB_RADIO 0.12f
#define HB_DANIO_PAJARO 1.0f
#define HB_DANIO_SUPERFICIE 0.5f
// HUEVO CODORNIZ
#define HC_RADIO 0.1f	// Minimo radio para evitar efecto tunneling
#define HC_DANIO_PAJARO 0.5f
#define HC_DANIO_SUPERFICIE 0.25f
#define HC_OFFSET_MAX 1.2f
#define HC_OFFSET_MIN 0.8f
// HUEVO POCHE
#define HP_RADIO 0.18f
#define HP_DANIO_PAJARO 1.0f
#define HP_DANIO_SUPERFICIE 0.25f
// HUEVO RELOJ
#define HR_RADIO 0.12f
#define HR_DANIO_PAJARO 1.0f
#define HR_DANIO_SUPERFICIE 2.0f
#define HR_DANIO_CERDITO 2.0f

// CONSTANTES DE CERDITOS
#define CE_VIDA 5.0f
#define CE_RADIO 0.3f

// CONSTANTES DE CATAPULTA
#define CAT_VIDA 10000.0f
#define CAT_MEDIO_ANCHO 0.5f
#define CAT_MEDIO_ALTO 0.3f

// CONSTANTES DE MONTICULO
#define M_VIDA 10.0f
#define M_ANCHO 0.55f
#define M_ALTO 0.58f

// CONSTANTES FRUTAS
#define F_RADIO 0.1f	// Minimo radio para evitar efecto tunneling
// MANZANA
#define FM_PUNTOS 10
// BANANA
#define FB_PUNTOS 15
// CEREZA
#define FC_PUNTOS 20

//CONSTANTES PARA EL SIMULADOR
#define NO_PAJARO    0
#define PAJARO_AZUL  1
#define PAJARO_ROJO  2
#define PAJARO_VERDE 3

#endif /* CONSTANTES_H_ */
