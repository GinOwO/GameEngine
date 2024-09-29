#pragma once

#include <math/Transform.h>

#include <graphics/Mesh.h>
#include <graphics/Shader.h>
#include <graphics/Material.h>

#include <components/GameComponent.h>

class MeshRenderer : public GameComponent {
    private:
	Mesh mesh;

	Material material;

    public:
	MeshRenderer() = delete;

	MeshRenderer(const Mesh &mesh, const Material &material);

	void input(float delta) override {};

	void update(float delta) override {};

	void render(Shader &shader) override;

	Material &get_material();
};
