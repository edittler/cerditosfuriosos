/* ATENCION: El RADIO de los cuerpos tienen que tener como minimo un valor de
 * 			 0.1f para evitar el efecto tunneling.
 *
 * ATENCION: Si los huevos adquieren mucha velocidad activar propiedad 'bullet'
 *           para evitar tunneling.
 */

#ifndef CONSTANTES_H_
#define CONSTANTES_H_

// CONSTANTES DE SUPERFICIES
#define ANCHO_CAJA 0.3f
// CAJA VIDRIO
#define VIDA_CAJA_VIDRIO 1
#define PUNTOS_CAJA_VIDRIO 10
// CAJA MADERA
#define VIDA_CAJA_MADERA 2
#define PUNTOS_CAJA_MADERA 20
// CAJA METAL
#define VIDA_CAJA_METAL 3
#define PUNTOS_CAJA_METAL 30

// CONSTANTES DE PAJAROS
#define GRUPO_FILTRO_PAJARO -1;
// PAJARO ROJO
#define VIDA_PAJARO_ROJO 0.5f
#define RADIO_PAJARO_ROJO 0.1f
#define RESTITUCION_PAJARO_ROJO 0.33f
// PAJARO VERDE
#define VIDA_PAJARO_VERDE 1.0f
#define RADIO_PAJARO_VERDE 0.2f
#define RESTITUCION_PAJARO_VERDE 0.2f
// PAJARO AZUL
#define VIDA_PAJARO_AZUL 1.0f
#define RADIO_PAJARO_AZUL 0.1f
#define RESTITUCION_PAJARO_AZUL 0.4f

// CONSTANTES DE DISPAROS
#define GRUPO_FILTRO_DISPARO -2;
#define RADIO_HUEVO_BLANCO 0.1f
#define RADIO_HUEVO_CODORNIZ 0.03f
#define RADIO_HUEVO_POCHE 0.1f
#define RADIO_HUEVO_RELOJ 0.05f

#endif /* CONSTANTES_H_ */
