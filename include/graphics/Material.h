/***************************************************************************
 * @file Material.h
 *
 * @brief Declares the Material class for material properties.
 *
 * This file contains the declaration of the Material class, which represents
 * the generic material properties of a 3D object, including its texture, color, and
 * specular properties.
 *
 ***************************************************************************/

#pragma once

#include <string>
#include <memory>
#include <unordered_map>

/***************************************************************************
 * @class Material
 *
 * @brief Represents material properties for a 3D object.
 *
 * The Material class includes generic properties for texture, color, and specular
 * attributes. It defines how the material interacts with light.
 *
 ***************************************************************************/
class Material {
	// TODO: comments
	std::unordered_map<std::string, std::shared_ptr<void> > property;

    public:
	Material();
	~Material();

	/***************************************************************************
	 * @brief Add a new property to the material.
	 *
	 * @param name The name of the new property.
	 * @param property Shared pointer to the new property to add.
	 ***************************************************************************/
	void add_property(const std::string &name,
			  std::shared_ptr<void> texture);

	/***************************************************************************
	 * @brief Gets the specified property of the material.
	 *
	 * Returns nullptr if not found
	 * 
	 * @param name The name of the property.
	 * @return The property as void*.
	 ***************************************************************************/
	void *get_property(const std::string &name) const noexcept;

	/***************************************************************************
	 * @brief Deletes the specified property of the material.
	 *
	 * 
	 * @param name Name of the property to delete.
	 ***************************************************************************/
	void delete_property(const std::string &name) noexcept;
};
