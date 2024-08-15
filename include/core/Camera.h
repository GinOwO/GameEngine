#pragma once

#include <math/Vector3f.h>

class Camera {
    private:
	static const Vector3f y_axis;

	Vector3f position;
	Vector3f forward;
	Vector3f up;

    public:
	Camera();

	void set_position(const Vector3f &vec) noexcept;
	void set_forward(const Vector3f &vec) noexcept;
	void set_up(const Vector3f &vec) noexcept;
	Vector3f get_position() const noexcept;
	Vector3f get_forward() const noexcept;
	Vector3f get_up() const noexcept;
};