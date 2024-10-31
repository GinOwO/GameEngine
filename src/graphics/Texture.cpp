#include <graphics/Texture.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/Specular.h>

#define STB_IMAGE_IMPLEMENTATION
#include <misc/stb_image.h>

#include <OpenEXR/ImfRgbaFile.h>
#include <OpenEXR/ImfInputFile.h>
#include <OpenEXR/ImfRgba.h>
#include <OpenEXR/ImfArray.h>

#include <string>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <exception>

const std::function<void(void *)> Specular::deleter{ [](void *ptr) {
	delete static_cast<Specular *>(ptr);
} };

const std::function<void(void *)> Texture::deleter{ [](void *ptr) {
	delete static_cast<Texture *>(ptr);
} };

std::unordered_map<std::string, std::weak_ptr<TextureResource> >
	Texture::texture_cache{};

Texture::Texture() {};

void Texture::bind() const
{
	if (texture_resource == nullptr || texture_resource->id == -1)
		return;
	glBindTexture(GL_TEXTURE_2D, texture_resource->id);
}

GLuint Texture::get_id() const noexcept
{
	return this->texture_resource->id;
}

std::shared_ptr<void> Texture::load_texture(const std::string &file_path)
{
	Texture *texture = new Texture();

	// Check cache for already loaded textures
	if (Texture::texture_cache.count(file_path)) {
		std::shared_ptr<TextureResource> resource =
			Texture::texture_cache[file_path].lock();
		if (resource) {
			texture->texture_resource = resource;
			return std::shared_ptr<void>(texture, Texture::deleter);
		}
	}

	if (texture->texture_resource == nullptr) {
		texture->texture_resource = std::make_shared<TextureResource>();
		texture_cache[file_path] = texture->texture_resource;
	}

	// Extract file extension to determine whether it's PNG or EXR
	std::string extension =
		file_path.substr(file_path.find_last_of('.') + 1);

	if (extension == "exr") {
		// Load EXR with OpenEXR
		try {
			Imf::RgbaInputFile exrFile(file_path.c_str());
			Imath::Box2i dw = exrFile.dataWindow();
			int32_t width = dw.max.x - dw.min.x + 1;
			int32_t height = dw.max.y - dw.min.y + 1;

			Imf::Array2D<Imf::Rgba> pixels(height, width);
			exrFile.setFrameBuffer(&pixels[0][0] - dw.min.x -
						       dw.min.y * width,
					       1, width);
			exrFile.readPixels(dw.min.y, dw.max.y);

			glGenTextures(1, &texture->texture_resource->id);
			glBindTexture(GL_TEXTURE_2D,
				      texture->texture_resource->id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
					GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
					GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
					GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width,
				     height, 0, GL_RGBA, GL_HALF_FLOAT,
				     &pixels[0][0]);

			glGenerateMipmap(GL_TEXTURE_2D);
		} catch (const std::exception &e) {
			std::cerr << "Failed to load EXR texture: " << e.what()
				  << '\n';
			throw std::runtime_error("Failed to load EXR texture");
		}
	} else if (extension == "png" || extension == "jpg" ||
		   extension == "jpeg") {
		// Load PNG with stb_image
		int32_t width, height, channels;
		unsigned char *data = stbi_load(file_path.c_str(), &width,
						&height, &channels, 0);

		if (!data) {
			std::cerr << "Failed to load PNG texture: " << file_path
				  << '\n';
			throw std::runtime_error("Failed to load PNG texture");
		}

		GLenum format;
		switch (channels) {
		case 1:
			format = GL_RED;
			break;
		case 4:
			format = GL_RGBA;
			break;
		default:
			format = GL_RGB;
		}

		glGenTextures(1, &texture->texture_resource->id);
		glBindTexture(GL_TEXTURE_2D, texture->texture_resource->id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
			     GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}

	else {
		std::cerr << "Unsupported texture format: " << file_path
			  << '\n';
		throw std::runtime_error("Unsupported texture format");
	}

	return std::shared_ptr<void>(texture, Texture::deleter);
}

bool Texture::operator==(const Texture &other) const noexcept
{
	return texture_resource->id == other.texture_resource->id;
}

#undef STB_IMAGE_IMPLEMENTATION
