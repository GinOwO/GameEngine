#include <graphics/ForwardAnimation.h>

#include <graphics/Shader.h>
#include <graphics/Texture.h>
#include <graphics/Material.h>

#include <physics/Skeleton.h>

#include <components/SharedGlobals.h>

ForwardAnimation::ForwardAnimation()
	: Shader()
{
	this->load_shader();
}

ForwardAnimation &ForwardAnimation::get_instance()
{
	static ForwardAnimation instance;
	return instance;
}

void ForwardAnimation::load_shader()
{
	this->load("shaders/forwardAnimation.vert",
		   "shaders/forwardAnimation.frag");

	// Add uniforms specific to animation
	this->add_uniform("model");
	this->add_uniform("MVP");
	this->add_uniform("boneMatrices");
}

void ForwardAnimation::update_uniforms(Transform *transform,
				       const Material &material)
{
	BaseCamera *camera = static_cast<BaseCamera *>(
		SharedGlobals::get_instance().main_camera);

	Matrix4f projected_matrix =
		Matrix4f::flip_matrix(camera->get_view_projection() *
				      transform->get_transformation());

	static_cast<Texture *>(material.get_property("diffuse"))->bind();

	this->set_uniform("MVP", projected_matrix);

	// Set bone matrices
	if (auto skeleton = static_cast<Skeleton *>(
		    material.get_property("skeleton"))) {
		for (size_t i = 0; i < skeleton->bones.size(); ++i) {
			std::string uniformName =
				"boneMatrices[" + std::to_string(i) + "]";
			this->set_uniform(
				uniformName,
				skeleton->bones[i].finalTransformation);
		}
	}
}
