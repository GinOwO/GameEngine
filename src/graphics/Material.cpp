#include <graphics/Material.h>

#include <math/Vector3f.h>

#include <core/SharedGlobals.h>

#include <memory>
#include <string>

const Material Material::None{};

Material::Material()
	: property{}
{
}

Material::~Material()
{
	property.clear();
}

Material &Material::add_property(const std::string &name,
				 std::shared_ptr<void> property)
{
	this->property[name] = property;
	return *this;
}

void *Material::get_property(const std::string &name) const noexcept
{
	if (!property.count(name))
		return (void *)(&Material::None);

	return property.at(name).get();
}

void Material::delete_property(const std::string &name) noexcept
{
	if (property.count(name))
		property.erase(name);
}