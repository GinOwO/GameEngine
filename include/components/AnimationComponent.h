#pragma once

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <math/Matrix4f.h>

#include <components/GameComponent.h>

#include <graphics/Mesh.h>

#include <unordered_map>
#include <string>
#include <vector>

class AnimationComponent : public GameComponent {
    private:
	struct BoneInfo {
		int id;
		Matrix4f offsetMatrix;
	};

	// Mapping bone name to its information
	std::unordered_map<std::string, BoneInfo> bone_map;
	std::vector<Matrix4f> bone_transforms;

	std::shared_ptr<Mesh> mesh;
	const aiScene *scene;
	Assimp::Importer importer;

	Matrix4f global_inverse_transform;
	float current_time;
	float duration;

	void read_node_hierarchy(float animation_time, const aiNode *node,
				 const Matrix4f &parent_transform);
	void calculate_bone_transforms(float time_in_seconds);
	const aiNodeAnim *find_node_anim(const aiAnimation *animation,
					 const std::string &node_name);

	Matrix4f interpolate_scaling(float animation_time,
				     const aiNodeAnim *node_anim);
	Matrix4f interpolate_rotation(float animation_time,
				      const aiNodeAnim *node_anim);
	Matrix4f interpolate_position(float animation_time,
				      const aiNodeAnim *node_anim);

    public:
	AnimationComponent(const std::string &model_path);
	~AnimationComponent() = default;

	void add_to_rendering_engine(bool id) override;
	void input(float delta) override {};
	void update(float delta) override;
	void render(Shader &shader) override;

	const std::vector<Matrix4f> &get_bone_transforms() const;
};
