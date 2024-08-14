#include <graphics/Vertex.h>

#include <math/Vector3f.h>

Vertex::Vertex()
{
	pos = Vector3f();
}

Vertex::Vertex(const Vector3f &pos)
{
	this->pos = Vector3f(pos);
}

Vector3f Vertex::getPos() const noexcept
{
	return this->pos;
}

void Vertex::setPos(const Vector3f &pos) noexcept
{
	this->pos = Vector3f(pos);
}