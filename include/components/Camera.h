

#pragma once

#include <math/Vector3f.h>
#include <math/Matrix4f.h>

#include <components/BaseCamera.h>
#include <components/GameComponent.h>

class Camera : public BaseCamera, public GameComponent {
	static bool perspective_set;

    public:
	void input(float delta) override {};

	Vector3f get_position() const noexcept override;

	Vector3f get_forward() const noexcept override;

	Vector3f get_up() const noexcept override;

	Vector3f get_left() const noexcept override;

	Vector3f get_right() const noexcept override;

	void set_projection(float fov, float aspect_ratio, float zNear,
			    float zFar) override;

	Matrix4f get_view_projection() const override;

	void render(Shader &) override {};
	void update(float delta) override {};
};
