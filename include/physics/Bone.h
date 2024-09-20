#pragma once

#include <math/Matrix4f.h>

#include <string>

struct Bone {
	int id;
	std::string name;
	Matrix4f offsetMatrix;
	Matrix4f finalTransform;
};