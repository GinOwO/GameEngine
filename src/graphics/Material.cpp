#include <graphics/Material.h>

const Material Material::None{};

/***************************************************************************
 * @brief Default constructor for Material.
 *
 * Initializes a Material object with default values.
 ***************************************************************************/
Material::Material()
	: property{}
{
}

/***************************************************************************
 * @brief Default destructor for Material.
 *
 * Frees properties
 ***************************************************************************/
Material::~Material()
{
	property.clear();
}

/***************************************************************************
 * @brief Add a new property to the material.
 *
 * @param name The name of the new property.
 * @param property The new property to add.
 ***************************************************************************/
void Material::add_property(const std::string &name,
			    std::shared_ptr<void> property)
{
	this->property[name] = property;
}

/***************************************************************************
 * @brief Gets the specified property of the material.
 *
 * Returns nullptr if not found
 * 
 * @param name The name of the property.
 * @return The property.
 ***************************************************************************/
void *Material::get_property(const std::string &name) const noexcept
{
	if (!property.count(name))
		return (void *)(&Material::None);

	return property.at(name).get();
}

/***************************************************************************
 * @brief Deletes the specified property of the material.
 *
 * 
 * @param name Name of the property to delete.
 ***************************************************************************/
void Material::delete_property(const std::string &name) noexcept
{
	if (property.count(name))
		property.erase(name);
}