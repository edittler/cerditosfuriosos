/* Encabezado que contiene todas las rutas de las imagenes.
 */

#ifndef CONSTANTESVISTAMODELO_H_
#define CONSTANTESVISTAMODELO_H_

// GENERAL
#define PATH_IMAGENES "../common/"

// FONDOS
#define FONDO_BOSQUE PATH_IMAGENES "images/background/Bosque.png"
#define FONDO_ISLA PATH_IMAGENES "images/background/Isla.png"

// CERDITOS
#define RUTA_CERDITO PATH_IMAGENES "images/scene/CerditoAtacando.png"

// CATAPULTA
#define RUTA_CATAPULTA PATH_IMAGENES "images/scene/Catapulta.png"

// MONTICULO
#define RUTA_MONTICULO_COMPLETO PATH_IMAGENES "images/scene/Monticulo10.png"

// PAJAROS
#define RUTA_PAJARO_ROJO_IZQ PATH_IMAGENES "images/scene/PajaroRojoI.png"
#define RUTA_PAJARO_ROJO_DER PATH_IMAGENES "images/scene/PajaroRojoD.png"
#define RUTA_PAJARO_VERDE_IZQ PATH_IMAGENES "images/scene/PajaroVerdeI.png"
#define RUTA_PAJARO_VERDE_DER PATH_IMAGENES "images/scene/PajaroVerdeD.png"
#define RUTA_PAJARO_AZUL_IZQ PATH_IMAGENES "images/scene/PajaroAzulI.png"
#define RUTA_PAJARO_AZUL_DER PATH_IMAGENES "images/scene/PajaroAzulD.png"

// SUPERFICIES
#define RUTA_CAJA_MADERA PATH_IMAGENES "images/scene/CajaMadera.png"
#define RUTA_CAJA_VIDRIO PATH_IMAGENES "images/scene/CajaVidrio.png"
#define RUTA_CAJA_METAL PATH_IMAGENES "images/scene/CajaMetal.png"

// DISPAROS
#define RUTA_HUEVO_BLANCO PATH_IMAGENES "images/scene/HuevoBlanco.png"
#define RUTA_HUEVO_CODORNIZ PATH_IMAGENES "images/scene/HuevoCodorniz.png"
#define RUTA_HUEVO_RELOJ PATH_IMAGENES "images/scene/HuevoReloj.png"

// VISTA
// Las escalas hacen referencia a cuantos pixeles equivalen a 1 metro
// medida usada en modelo.
#define AJUSTE_ESCALA_VISTA 100
#define ESCALA_IMAGENES 100.0f
#define AJUSTE_ESCALA_IMAGENES (ESCALA_IMAGENES / AJUSTE_ESCALA_VISTA)
#define DELTA_LOOP 30000

#endif /* CONSTANTESVISTAMODELO_H_ */
