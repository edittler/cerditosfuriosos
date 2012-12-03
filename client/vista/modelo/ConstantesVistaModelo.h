/* Encabezado que contiene todas las rutas de las imagenes.
 */

#ifndef CONSTANTESVISTAMODELO_H_
#define CONSTANTESVISTAMODELO_H_

// GENERAL
#define PATH_IMAGENES "../common/images/"
#define PATH_IMAGENES_LOCAL "imagenes/"

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

// TIEMPO
#define POSICION_TIEMPO_X 8
#define POSICION_TIEMPO_Y 5

// VISTA
// Las escalas hacen referencia a cuantos pixeles equivalen a 1 metro
// medida usada en modelo.
#define AJUSTE_ESCALA_VISTA 70
#define ESCALA_IMAGENES 100.0f
#define AJUSTE_ESCALA_IMAGENES (ESCALA_IMAGENES / AJUSTE_ESCALA_VISTA)
#define WAIT_SPLASH 2  // en segundos
#define WAIT_FINALIZAR 4  // en segundos
#define ESCALA_TEXTO 2.5f
#define COLOR_TEXTO 50000

// MENU
#define RUTA_FONDO_PANEL_INICIAL PATH_IMAGENES_LOCAL "menues/MenuPrincipal.png"
#define RUTA_FONDO_PANEL_UN_JUGADOR PATH_IMAGENES_LOCAL "menues/UnJugador.png"
#define RUTA_FONDO_PANEL_MULTIJUGADOR PATH_IMAGENES_LOCAL "menues/Multijugador.png"
#define RUTA_FONDO_PANEL_CONFIGURACION PATH_IMAGENES_LOCAL "menues/Configuracion.png"
#define RUTA_FONDO_PANEL_CREAR_PARTIDA PATH_IMAGENES_LOCAL "menues/CrearPartida.png"
#define RUTA_FONDO_PANEL_UNIRSE_PARTIDA PATH_IMAGENES_LOCAL "menues/UnirseAPartida.png"
#define RUTA_FONDO_PANEL_RECORDS PATH_IMAGENES_LOCAL "menues/Records.png"
#define RUTA_FONDO_PANEL_ESPERANDO_JUGADORES PATH_IMAGENES_LOCAL "menues/EsperandoJugadores.png"

// VARIOS
#define SPLASH_IMAGEN PATH_IMAGENES_LOCAL "varias/Splash.png"
#define GAME_OVER_IMAGEN PATH_IMAGENES_LOCAL "varias/GameOver.png"
#define WIN_IMAGEN PATH_IMAGENES_LOCAL "varias/Winner.png"

#define ANCHO_VENTANA 600
#define ALTO_VENTANA 600

#endif /* CONSTANTESVISTAMODELO_H_ */
