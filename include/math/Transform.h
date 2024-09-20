

#pragma once

#include <math/Vector3f.h>
#include <math/Matrix4f.h>
#include <math/Quaternion.h>

#include <components/BaseCamera.h>

class Transform {
    private:
	Vector3f translation, prev_translation;
	Quaternion rotation, prev_rotation;
	Vector3f scale, prev_scale;

	Matrix4f parent_matrix;
	bool first_update = true;

    public:
	Transform *parent = nullptr;

	Transform();

	Vector3f get_translation() const noexcept;

	Quaternion get_rotation() const noexcept;

	Vector3f get_scale() const noexcept;

	Transform &set_translation(float x, float y, float z);

	Transform &set_translation(Vector3f translation);

	Transform &set_rotation(Quaternion rotation);

	Transform &set_scale(Vector3f scale);

	Transform &set_scale(float x, float y, float z);

	Matrix4f get_transformation() noexcept;

	Matrix4f get_projected_camera(BaseCamera *camera) noexcept;

	bool has_changed() noexcept;

	Vector3f get_transformed_position() noexcept;
	Quaternion get_transformed_rotation() noexcept;
	void update() noexcept;
	Transform &rotate(const Vector3f &axis, float angle);
	void look_at(const Vector3f &point, const Vector3f &up) noexcept;
	Quaternion look_at_direction(const Vector3f &point,
				     const Vector3f &up) noexcept;
};
