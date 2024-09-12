#include <graphics/Vertex.h>

#include <math/Vector2f.h>
#include <math/Vector3f.h>

Vertex::Vertex()
{
	pos = Vector3f();
	texCoord = Vector2f();
}

Vertex::Vertex(const Vector3f &pos)
	: Vertex(pos, { 0, 0 })
{
}

Vertex::Vertex(const Vector3f &pos, const Vector2f &texCoord)
	: Vertex(pos, texCoord, { 0, 0, 0 })
{
}

Vertex::Vertex(const Vector3f &pos, const Vector2f &texCoord,
	       const Vector3f &normal)
{
	this->pos = Vector3f(pos);
	this->texCoord = Vector2f(texCoord);
	this->normal = Vector3f(normal);
}

Vector3f Vertex::get_pos() const noexcept
{
	return this->pos;
}

void Vertex::set_pos(const Vector3f &pos) noexcept
{
	this->pos = Vector3f(pos);
}

Vector2f Vertex::get_texCoord() const noexcept
{
	return this->texCoord;
}

void Vertex::set_texCoord(const Vector2f &texCoord) noexcept
{
	this->texCoord = Vector2f(texCoord);
}

Vector3f Vertex::get_normal() const noexcept
{
	return this->normal;
}

void Vertex::set_normal(const Vector3f &normal) noexcept
{
	this->normal = Vector3f(normal);
}
