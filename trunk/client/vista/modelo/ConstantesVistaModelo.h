/* Encabezado que contiene todas las rutas de las imagenes.
 */

#ifndef CONSTANTESVISTAMODELO_H_
#define CONSTANTESVISTAMODELO_H_

// GENERAL
#define PATH_IMAGENES "../common/images/"

// FONDOS
#define FONDO_BOSQUE PATH_IMAGENES "background/Bosque.png"
#define FONDO_ISLA PATH_IMAGENES "background/Isla.png"

// SUELOS
#define SUELO_BOSQUE PATH_IMAGENES "background/SueloBosque.png"

// CERDITOS
#define RUTA_CERDITO PATH_IMAGENES "scene/CerditoAtacando.png"

// CATAPULTA
#define RUTA_CATAPULTA PATH_IMAGENES "scene/Catapulta.png"

// FRUTAS
#define RUTA_BANANA PATH_IMAGENES "scene/Banana.png"
#define RUTA_CEREZA PATH_IMAGENES "scene/Cereza.png"
#define RUTA_MANZANA PATH_IMAGENES "scene/Manzana.png"

// MONTICULO
#define RUTA_MONTICULO_COMPLETO PATH_IMAGENES "scene/Monticulo10.png"

// PAJAROS
#define RUTA_PAJARO_ROJO_IZQ PATH_IMAGENES "scene/PajaroRojoI.png"
#define RUTA_PAJARO_ROJO_DER PATH_IMAGENES "scene/PajaroRojoD.png"
#define RUTA_PAJARO_VERDE_IZQ PATH_IMAGENES "scene/PajaroVerdeI.png"
#define RUTA_PAJARO_VERDE_DER PATH_IMAGENES "scene/PajaroVerdeD.png"
#define RUTA_PAJARO_AZUL_IZQ PATH_IMAGENES "scene/PajaroAzulI.png"
#define RUTA_PAJARO_AZUL_DER PATH_IMAGENES "scene/PajaroAzulD.png"

// SUPERFICIES
#define RUTA_CAJA_MADERA PATH_IMAGENES "scene/CajaMadera.png"
#define RUTA_CAJA_VIDRIO PATH_IMAGENES "scene/CajaVidrio.png"
#define RUTA_CAJA_METAL PATH_IMAGENES "scene/CajaMetal.png"

// DISPAROS
#define RUTA_HUEVO_BLANCO PATH_IMAGENES "scene/HuevoBlanco.png"
#define RUTA_HUEVO_CODORNIZ PATH_IMAGENES "scene/HuevoCodorniz.png"
#define RUTA_HUEVO_POCHE PATH_IMAGENES "scene/HuevoPoche.png"
#define RUTA_HUEVO_RELOJ PATH_IMAGENES "scene/HuevoReloj.png"

// VISTA
// Las escalas hacen referencia a cuantos pixeles equivalen a 1 metro
// medida usada en modelo.
#define AJUSTE_ESCALA_VISTA 70
#define ESCALA_IMAGENES 100.0f
#define AJUSTE_ESCALA_IMAGENES (ESCALA_IMAGENES / AJUSTE_ESCALA_VISTA)
#define DELTA_LOOP 30000

#endif /* CONSTANTESVISTAMODELO_H_ */
