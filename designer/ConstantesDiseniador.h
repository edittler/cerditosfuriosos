#ifndef _CONSTANTES_DISENIADOR_H_
#define _CONSTANTES_DISENIADOR_H_

/**
 * Aqui se definen constantes que determinan los valores por los que el usuario
 * puede optar en la creacion de mundos y niveles.
 */
#define MAXIMA_CANTIDAD_JUGADORES 5.0
// Las siguientes constantes estan en unidades del modelo
#define ANCHO_ESCENARIO_CHICO 10
#define ALTO_ESCENARIO_CHICO 8
#define ANCHO_ESCENARIO_MEDIANO 11
#define ALTO_ESCENARIO_MEDIANO 9
#define ANCHO_ESCENARIO_GRANDE 12
#define ALTO_ESCENARIO_GRANDE 10

#define MAXIMA_DURACION_NIVEL 60.0

// Ruta de la carpeta donde se almacenan los archivos del mundo
#define RUTA_CARPETA_MUNDOS "../common/mundos/"

// Ruta relativa al ejecutable que carga los escenarios de los fondos
#define RUTA_FONDOS "../common/images/background/"
#define RUTA_SUELO "../common/images/floor/SueloBosque.png"

// Ruta de las imagenes que se colocaran en los botones
#define RUTA_ITEM_CAJA_MADERA "items/ItemCajaMadera.png"
#define RUTA_ITEM_CAJA_METAL "items/ItemCajaMetal.png"
#define RUTA_ITEM_CAJA_VIDRIO "items/ItemCajaVidrio.png"
#define RUTA_ITEM_CERDO "items/ItemCerdo.png"
#define RUTA_ITEM_HUEVOS "items/ItemMonticulo.png"
#define RUTA_ITEM_BANANA "items/ItemBanana.png"
#define RUTA_ITEM_CEREZA "items/ItemCereza.png"
#define RUTA_ITEM_MANZANA "items/ItemManzana.png"
#define RUTA_ITEM_CATAPULTA "items/ItemCatapulta.png"
// Ruta de las imagenes que se colocaran al arrastrar un boton
#define RUTA_CAJA_MADERA "../common/images/scene/CajaMadera.png"
#define RUTA_CAJA_METAL "../common/images/scene/CajaMetal.png"
#define RUTA_CAJA_VIDRIO "../common/images/scene/CajaVidrio.png"
#define RUTA_CERDO "../common/images/scene/CerditoAtacando.png"
#define RUTA_HUEVOS "../common/images/scene/Monticulo10.png"
#define RUTA_BANANA "../common/images/scene/Banana.png"
#define RUTA_CEREZA "../common/images/scene/Cereza.png"
#define RUTA_MANZANA "../common/images/scene/Manzana.png"
#define RUTA_CATAPULTA "../common/images/scene/Catapulta.png"
// Dimensiones de los paneles del wizard en pixeles
#define ANCHO_WIZARD 600
#define ALTO_WIZARD 400
// Dimensiones de los objetos del lienzo en pixeles
#define ANCHO_BANANA 21
#define ALTO_BANANA 21
#define ANCHO_CAJA_MADERA 42
#define ALTO_CAJA_MADERA 42
#define ANCHO_CAJA_METAL 42
#define ALTO_CAJA_METAL 42
#define ALTO_CAJA_VIDRIO 42
#define ANCHO_CAJA_VIDRIO 42
#define ANCHO_CATAPULTA 42
#define ALTO_CATAPULTA 42
#define ALTO_CERDO 42
#define ANCHO_CERDO 42
#define ANCHO_CEREZA 21
#define ALTO_CEREZA 21
#define ALTO_HUEVOS 41
#define ANCHO_HUEVOS 39
#define ANCHO_MANZANA 21
#define ALTO_MANZANA 21
#define ALTO_SUELO 28
// Pajaros
#define TIEMPO_GENERACION_MINIMO 100.0
#define TIEMPO_GENERACION_MAXIMO 1000.0
// Factor de conversion entre las unidades del modelo y las de la vista
#define PIXELES_SOBRE_METRO 70

#endif
