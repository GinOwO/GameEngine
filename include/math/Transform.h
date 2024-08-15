#pragma once

#include <math/Vector3f.h>
#include <math/Matrix4f.h>

class Transform {
    private:
	Vector3f translation;
	Vector3f rotation;
	Vector3f scale;

    public:
	Transform();

	Vector3f get_translation();
	Vector3f get_rotation();
	Vector3f get_scale();

	void set_translation(float x, float y, float z);
	void set_translation(Vector3f translation);

	void set_rotation(Vector3f rotation);
	void set_rotation(float x, float y, float z);

	void set_scale(Vector3f rotation);
	void set_scale(float x, float y, float z);

	Matrix4f get_transformation();
};