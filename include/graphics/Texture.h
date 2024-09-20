

#pragma once

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/resource_management/TextureResource.h>

#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

class Texture {
    private:
	std::shared_ptr<TextureResource> texture_resource;
	static std::unordered_map<std::string, std::weak_ptr<TextureResource> >
		texture_cache;

    public:
	Texture();

	const static Texture None; // TODO: comment
	const static std::function<void(void *)> deleter;

	GLuint get_id() const noexcept;

	void bind() const;

	static std::shared_ptr<void> load_texture(const std::string &file_path);

	// TODO: comment
	bool operator==(const Texture &other) const noexcept;
};
