/* Redefinición de los tipos (nombres de las clases) de la librería TinyXML
 * para que sean más simple de programar.
 */

#ifndef XMLTYPES_H_
#define XMLTYPES_H_

// Standard C++ Library Includes
#include <exception>

// Project Includes
#include "tinyxml.h"

// Redefinición del nombre del Documento XML
typedef TiXmlDocument XMLDocument;

// Redefinición del nombre de la Declaración XML
typedef TiXmlDeclaration XMLDeclaration;

// Redefinición del nombre del Elemento XML
typedef TiXmlElement XMLNode;

// Redefinición del nombre del Atributo de Nodo XML
typedef TiXmlAttribute XMLAtributte;

// Redefinición del nombre del Texto XML
typedef TiXmlText XMLText;

// Redefinición del nombre del Comentario XML
typedef TiXmlComment XMLComment;

class XMLSerializacionException: public std::exception {
};

#endif  /* XMLTYPES_H_ */
