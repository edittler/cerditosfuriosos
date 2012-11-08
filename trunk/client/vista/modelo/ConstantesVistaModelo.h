/* Encabezado que contiene todas las rutas de las imagenes.
 */

#ifndef CONSTANTESVISTAMODELO_H_
#define CONSTANTESVISTAMODELO_H_

// CERDITOS
#define RUTA_CERDITO "imagenes/escena/CerditoAtacando.png"

// MONTICULO
#define RUTA_MONTICULO_COMPLETO "imagenes/escena/Monticulo10.png"

// PAJAROS
#define RUTA_PAJARO_ROJO_IZQ "imagenes/escena/PajaroRojoI.png"
#define RUTA_PAJARO_ROJO_DER "imagenes/escena/PajaroRojoD.png"
#define RUTA_PAJARO_VERDE_IZQ "imagenes/escena/PajaroVerdeI.png"
#define RUTA_PAJARO_VERDE_DER "imagenes/escena/PajaroVerdeD.png"
#define RUTA_PAJARO_AZUL_IZQ "imagenes/escena/PajaroAzulI.png"
#define RUTA_PAJARO_AZUL_DER "imagenes/escena/PajaroAzulD.png"

// SUPERFICIES
#define RUTA_CAJA_MADERA "imagenes/escena/CajaMadera.png"
#define RUTA_CAJA_VIDRIO "imagenes/escena/CajaVidrio.png"
#define RUTA_CAJA_METAL "imagenes/escena/CajaMetal.png"

// DISPAROS
#define RUTA_HUEVO_BLANCO "imagenes/escena/HuevoBlanco.png"
#define RUTA_HUEVO_CODORNIZ "imagenes/escena/HuevoCodorniz.png"
#define RUTA_HUEVO_RELOJ "imagenes/escena/HuevoReloj.png"

// VISTA
// Las escalas hacen referencia a cuantos pixeles equivalen a 1 metro
// medida usada en modelo.
#define AJUSTE_ESCALA_VISTA 70
#define ESCALA_IMAGENES 100.0f
#define AJUSTE_ESCALA_IMAGENES (ESCALA_IMAGENES / AJUSTE_ESCALA_VISTA)
#define DELTA_LOOP 30000

#endif /* CONSTANTESVISTAMODELO_H_ */
