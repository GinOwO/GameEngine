#pragma once

#include <math/Vector3f.h>

class Camera {
    public:
	Camera(const Camera &) = delete;
	Camera &operator=(const Camera &) = delete;

	static Camera &get_instance();

    private:
	static const Vector3f y_axis;

	Vector3f position;
	Vector3f forward;
	Vector3f up;

	Camera();
	Camera(const Vector3f &position, const Vector3f &forward,
	       const Vector3f &up);

    public:
	void input();

	void set_position(const Vector3f &vec) noexcept;
	void set_forward(const Vector3f &vec) noexcept;
	void set_up(const Vector3f &vec) noexcept;
	Vector3f get_position() const noexcept;

	Vector3f get_forward() const noexcept;
	Vector3f get_up() const noexcept;
	Vector3f get_left() const noexcept;
	Vector3f get_right() const noexcept;

	void move_camera(const Vector3f &direction, float amount) noexcept;
	void rotate_x(float angle) noexcept;
	void rotate_y(float angle) noexcept;
};