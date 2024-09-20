#include <graphics/Material.h>

const Material Material::None{};

Material::Material()
	: property{}
{
}

Material::~Material()
{
	property.clear();
}

void Material::add_property(const std::string &name,
			    std::shared_ptr<void> property)
{
	this->property[name] = property;
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