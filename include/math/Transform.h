#pragma once

#include <math/Vector3f.h>
#include <math/Matrix4f.h>

class Transform {
    private:
	static float zNear;
	static float zFar;
	static float width;
	static float height;
	static float fov;

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

	static void set_projection(float fov, float width, float height,
				   float zNear, float zFar);

	Matrix4f get_transformation();
	Matrix4f get_projected_transformation();
};