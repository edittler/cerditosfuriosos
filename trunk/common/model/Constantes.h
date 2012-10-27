/* ATENCION: El RADIO de los cuerpos tienen que tener como minimo un valor de
 * 			 0.1f para evitar el efecto tunneling.
 *
 * ATENCION: Si los huevos adquieren mucha velocidad activar propiedad 'bullet'
 *           para evitar tunneling.
 */

#ifndef CONSTANTES_H_
#define CONSTANTES_H_

#include "ConstantesColisiones.h"

// CONSTANTES DE SUPERFICIES
#define MEDIO_ANCHO_CAJA 0.2f
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
#define PR_RADIO 0.1f
#define PR_RESTITUCION 0.33f
#define PR_DANIO_CERDITO 1.0f
#define PR_DANIO_SUPERFICIE 0.5f
// PAJARO VERDE
#define PV_VIDA 1.0f
#define PV_RADIO 0.15f
#define PV_RESTITUCION 0.2f
#define PV_DANIO_CERDITO 2.0f
#define PV_DANIO_SUPERFICIE 1.0f
// PAJARO AZUL
#define PA_VIDA 1.0f
#define PA_RADIO 0.1f
#define PA_RESTITUCION 0.4f
#define PA_DANIO_CERDITO 1.0f
#define PA_DANIO_SUPERFICIE 0.5f

// CONSTANTES DE DISPAROS
// HUEVO BLANCO
#define HB_RADIO 0.15f
#define HB_DANIO_PAJARO 1.0f
#define HB_DANIO_SUPERFICIE 0.5f
// HUEVO CODORNIZ
#define HC_RADIO 0.1f
#define HC_DANIO_PAJARO 0.5f
#define HC_DANIO_SUPERFICIE 0.25f
// HUEVO POCHE
#define HP_RADIO 0.15f
#define HP_DANIO_PAJARO 1.0f
#define HP_DANIO_SUPERFICIE 0.25f
// HUEVO RELOJ
#define HR_RADIO 0.15f
#define HR_DANIO_PAJARO 1.0f
#define HR_DANIO_SUPERFICIE 2.0f
#define HR_DANIO_CERDITO 2.0f

// CONSTANTES CERDITO Y MONTICULO
#define C_VIDA 5.0f
#define C_RADIO 0.3f
#define M_VIDA 10.0f

#endif /* CONSTANTES_H_ */
