#include "Monticulo.h"
#include "Constantes.h"

Monticulo::Monticulo(b2Body* body) {
	// Defino los atributos de clase
	this->vida = M_VIDA;
	this->cuerpo = body;

	// Paso una referencia de este objeto al body de Box2D
	this->cuerpo->SetUserData(this);

	// Defino la forma del monticulo (triangulo)
	b2PolygonShape polygonShape;
	int32 verticesTriangulo = 3;

	// TODO Setear los valores correctos de los vertices
	b2Vec2 vertices[3];
	vertices[0].Set(0.0f, 0.0f);
	vertices[1].Set(1.0f, 0.0f);
	vertices[2].Set(0.0f, 1.0f);

	polygonShape.Set(vertices, verticesTriangulo);

	// Defino las propiedades del cuerpo
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 0.8f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.categoryBits = CATEGORY_MONTICULO;
	fixtureDef.filter.maskBits = MASK_MONTICULO;
	this->cuerpo->CreateFixture(&fixtureDef);
}

Monticulo::~Monticulo() {
	// TODO Auto-generated destructor stub
}

