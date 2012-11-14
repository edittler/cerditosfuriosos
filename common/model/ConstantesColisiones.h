/* CONSTANTES DE CATEGORIAS Y MASCARAS DE LOS OBJETOS DE LA ESCENA
 * Para aplicar filtros en las colisiones.
 *
 * Manipular con EXTREMO CUIDADO!!
 * En caso de dudas, consultar con Ezequiel Perez Dittler
 */

#ifndef CONSTANTESCOLISIONES_H_
#define CONSTANTESCOLISIONES_H_

// GRUPOS
#define GROUP_PAJARO	-1
#define GROUP_DISPARO	-2

// CATEGORIAS
/* La categoria 0x0001 es la que se asigna por default, que en nuestro caso
 * será la del suelo y catapulta.
 */
#define CATEGORY_SUPERFICIE		0x0002 	// Binario 0000000000000010
#define CATEGORY_PAJARO			0X0004 	// Binario 0000000000000100
#define CATEGORY_DISPARO		0x0008 	// Binario 0000000000001000
#define CATEGORY_CERDITO		0x0010 	// Binario 0000000000010000
#define CATEGORY_MONTICULO		0x0020 	// Binario 0000000000100000
#define CATEGORY_FRUTA			0x0040 	// Binario 0000000001000000
#define CATEGORY_SUELO			0x0080 	// Binario 0000000010000000

// SUMA DE CATEGORIAS
#define SUPERFICIE_AND_PAJARO	0x0006 	// Binario 0000000000000110
#define SUPERFICIE_AND_DISPARO	0x000A 	// Binario 0000000000001010
#define PAJARO_AND_DISPARO		0x000C 	// Binario 0000000000001100
#define CERDITO_AND_PAJARO		0X0014 	// Binario 0000000000010100
#define CERDITO_AND_DISPARO		0x0018 	// Binario 0000000000011000
#define MONTICULO_AND_PAJARO	0x0024 	// Binario 0000000000100100
#define MONTICULO_AND_DISPARO	0x0028 	// Binario 0000000000101000
#define FRUTA_AND_PAJARO		0x0044 	// Binario 0000000001000100
#define FRUTA_AND_DISPARO		0x0048 	// Binario 0000000001001000
#define SUELO_AND_DISPARO		0x0088 	// Binario 0000000010000100
#define SUELO_AND_DISPARO		0x0088 	// Binario 0000000010001000

// MASCARAS
#define MASK_SUPERFICIE			0x000D 	// Binario 0000000000001101
#define MASK_PAJARO				0X00FB 	// Binario 0000000011111011
#define MASK_DISPARO			0X00F7 	// Binario 0000000011110111
#define MASK_CERDITO			0x000D 	// Binario 0000000000001101
#define MASK_MONTICULO			0x000D 	// Binario 0000000000001101
#define MASK_FRUTA				0x000D 	// Binario 0000000000001101
#define MASK_SUELO				0xFFFF 	// Binario 1111111111111111

#endif /* CONSTANTESCOLISIONES_H_ */