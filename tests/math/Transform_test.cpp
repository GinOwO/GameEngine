#include <gtest/gtest.h>
#include <math/Vector3f.h>
#include <math/Matrix4f.h>
#include <core/Camera.h>
#include <math/Transform.h>

// Test for default constructor
TEST(TransformTest, DefaultConstructor)
{
	Transform transform;

	Vector3f translation = transform.get_translation();
	Vector3f rotation = transform.get_rotation();
	Vector3f scale = transform.get_scale();

	EXPECT_EQ(translation, Vector3f(0.0f, 0.0f, 0.0f));
	EXPECT_EQ(rotation, Vector3f(0.0f, 0.0f, 0.0f));
	EXPECT_EQ(scale,
		  Vector3f(1.0f, 1.0f, 1.0f)); // Assuming scale defaults to 1
}

// Test for translation setter and getter
TEST(TransformTest, TranslationSetterGetter)
{
	Transform transform;
	Vector3f translation(10.0f, 20.0f, 30.0f);

	transform.set_translation(translation);

	EXPECT_EQ(transform.get_translation(), translation);
}

// Test for rotation setter and getter
TEST(TransformTest, RotationSetterGetter)
{
	Transform transform;
	Vector3f rotation(90.0f, 45.0f, 30.0f);

	transform.set_rotation(rotation);

	EXPECT_EQ(transform.get_rotation(), rotation);
}

// Test for scale setter and getter
TEST(TransformTest, ScaleSetterGetter)
{
	Transform transform;
	Vector3f scale(2.0f, 2.0f, 2.0f);

	transform.set_scale(scale);

	EXPECT_EQ(transform.get_scale(), scale);
}
