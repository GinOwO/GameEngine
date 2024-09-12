/***************************************************************************
 * @file Vertex.h
 *
 * @brief Declares the Vertex class for representing mesh vertices.
 *
 * This file contains the declaration of the Vertex class, which represents
 * a vertex in a mesh, including its position, normal, and texture coordinates.
 *
 ***************************************************************************/

#pragma once

#include <math/Vector2f.h>
#include <math/Vector3f.h>

/***************************************************************************
 * @class Vertex
 *
 * @brief Represents a vertex with position, normal, and texture coordinates.
 *
 * The Vertex class encapsulates the attributes of a vertex in a mesh, including
 * its position, normal vector, and texture coordinates.
 *
 ***************************************************************************/
class Vertex {
    private:
	Vector3f pos; /**< Position of the vertex. */
	Vector3f normal; /**< Normal vector of the vertex. */
	Vector2f texCoord; /**< Texture coordinates of the vertex. */

    public:
	static const int SIZE = 8; /**< Size of the vertex data. */

	Vertex();
	Vertex(const Vector3f &pos);
	Vertex(const Vector3f &pos, const Vector2f &texCoord);
	Vertex(const Vector3f &pos, const Vector2f &texCoord,
	       const Vector3f &normal);

	/***************************************************************************
	 * @brief Gets the position of the vertex.
	 *
	 * @return The position vector.
	 ***************************************************************************/
	Vector3f get_pos() const noexcept;

	/***************************************************************************
	 * @brief Sets the position of the vertex.
	 *
	 * @param pos The new position vector.
	 ***************************************************************************/
	void set_pos(const Vector3f &pos) noexcept;

	/***************************************************************************
	 * @brief Gets the normal vector of the vertex.
	 *
	 * @return The normal vector.
	 ***************************************************************************/
	Vector3f get_normal() const noexcept;

	/***************************************************************************
	 * @brief Sets the normal vector of the vertex.
	 *
	 * @param pos The new normal vector.
	 ***************************************************************************/
	void set_normal(const Vector3f &pos) noexcept;

	/***************************************************************************
	 * @brief Gets the texture coordinates of the vertex.
	 *
	 * @return The texture coordinates.
	 ***************************************************************************/
	Vector2f get_texCoord() const noexcept;

	/***************************************************************************
	 * @brief Sets the texture coordinates of the vertex.
	 *
	 * @param texCoord The new texture coordinates.
	 ***************************************************************************/
	void set_texCoord(const Vector2f &texCoord) noexcept;
};
