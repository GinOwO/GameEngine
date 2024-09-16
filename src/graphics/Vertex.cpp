#include <graphics/Vertex.h>

#include <math/Vector2f.h>
#include <math/Vector3f.h>

/***************************************************************************
 * @brief Default constructor for Vertex.
 *
 * Initializes a Vertex with default values for position (Vector3f()), 
 * texture coordinates (Vector2f()), and normal (Vector3f()).
 ***************************************************************************/
Vertex::Vertex()
{
	pos = Vector3f();
	texCoord = Vector2f();
}

/***************************************************************************
 * @brief Constructs a Vertex with a specified position.
 *
 * Initializes a Vertex with the given position and default texture 
 * coordinates (Vector2f()) and normal (Vector3f()).
 *
 * @param pos The position of the vertex.
 ***************************************************************************/
Vertex::Vertex(const Vector3f &pos)
	: Vertex(pos, { 0, 0 })
{
}

/***************************************************************************
 * @brief Constructs a Vertex with specified position and texture coordinates.
 *
 * Initializes a Vertex with the given position, texture coordinates, and 
 * default normal (Vector3f()).
 *
 * @param pos The position of the vertex.
 * @param texCoord The texture coordinates of the vertex.
 ***************************************************************************/
Vertex::Vertex(const Vector3f &pos, const Vector2f &texCoord)
	: Vertex(pos, texCoord, { 0, 0, 0 })
{
}

/***************************************************************************
 * @brief Constructs a Vertex with specified position, texture coordinates, 
 *	and normal.
 *
 * Initializes a Vertex with the given position, texture coordinates, and 
 * normal.
 *
 * @param pos The position of the vertex.
 * @param texCoord The texture coordinates of the vertex.
 * @param normal The normal vector of the vertex.
 ***************************************************************************/
Vertex::Vertex(const Vector3f &pos, const Vector2f &texCoord,
	       const Vector3f &normal)
{
	this->pos = Vector3f(pos);
	this->texCoord = Vector2f(texCoord);
	this->normal = Vector3f(normal);
}

/***************************************************************************
 * @brief Gets the position of the vertex.
 *
 * Retrieves the position vector of the vertex.
 *
 * @return The position of the vertex.
 ***************************************************************************/
Vector3f Vertex::get_pos() const noexcept
{
	return this->pos;
}

/***************************************************************************
 * @brief Sets the position of the vertex.
 *
 * Updates the position vector of the vertex.
 *
 * @param pos The new position of the vertex.
 ***************************************************************************/
void Vertex::set_pos(const Vector3f &pos) noexcept
{
	this->pos = Vector3f(pos);
}

/***************************************************************************
 * @brief Gets the texture coordinates of the vertex.
 *
 * Retrieves the texture coordinates of the vertex.
 *
 * @return The texture coordinates of the vertex.
 ***************************************************************************/
Vector2f Vertex::get_texCoord() const noexcept
{
	return this->texCoord;
}

/***************************************************************************
 * @brief Sets the texture coordinates of the vertex.
 *
 * Updates the texture coordinates of the vertex.
 *
 * @param texCoord The new texture coordinates of the vertex.
 ***************************************************************************/
void Vertex::set_texCoord(const Vector2f &texCoord) noexcept
{
	this->texCoord = Vector2f(texCoord);
}

/***************************************************************************
 * @brief Gets the normal vector of the vertex.
 *
 * Retrieves the normal vector of the vertex.
 *
 * @return The normal vector of the vertex.
 ***************************************************************************/
Vector3f Vertex::get_normal() const noexcept
{
	return this->normal;
}

/***************************************************************************
 * @brief Sets the normal vector of the vertex.
 *
 * Updates the normal vector of the vertex.
 *
 * @param normal The new normal vector of the vertex.
 ***************************************************************************/
void Vertex::set_normal(const Vector3f &normal) noexcept
{
	this->normal = Vector3f(normal);
}
