

#pragma once

#include <math/Vector3f.h>
#include <math/Matrix4f.h>

class BaseCamera {
    protected:
	Matrix4f projection;

    public:
	virtual void input(float delta = 0) = 0;

	virtual Vector3f get_position() const noexcept = 0;

	virtual Vector3f get_forward() const noexcept = 0;

	virtual Vector3f get_up() const noexcept = 0;

	virtual Vector3f get_left() const noexcept = 0;

	virtual Vector3f get_right() const noexcept = 0;

	virtual void set_projection(float fov, float aspect_ratio, float zNear,
				    float zFar) = 0;

	virtual Matrix4f get_view_projection() const = 0;
};
