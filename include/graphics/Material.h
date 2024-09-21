#pragma once

#include <string>
#include <memory>
#include <unordered_map>

class Material {
	std::unordered_map<std::string, std::shared_ptr<void> > property;

    public:
	static const Material None;

	Material();
	~Material();

	Material &add_property(const std::string &name,
			       std::shared_ptr<void> texture);

	void *get_property(const std::string &name) const noexcept;

	void delete_property(const std::string &name) noexcept;
};
