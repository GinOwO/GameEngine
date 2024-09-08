#include <gtest/gtest.h>
#include <math/Vector3f.h>

// Test default constructor
TEST(Vector3fTest, DefaultConstructor)
{
	Vector3f v;
	EXPECT_FLOAT_EQ(v.getX(), 0.0f);
	EXPECT_FLOAT_EQ(v.getY(), 0.0f);
	EXPECT_FLOAT_EQ(v.getZ(), 0.0f);
}

// Test parameterized constructor
TEST(Vector3fTest, ParameterizedConstructor)
{
	Vector3f v(1.0f, 2.0f, 3.0f);
	EXPECT_FLOAT_EQ(v.getX(), 1.0f);
	EXPECT_FLOAT_EQ(v.getY(), 2.0f);
	EXPECT_FLOAT_EQ(v.getZ(), 3.0f);
}

// Test setters and getters
TEST(Vector3fTest, SettersAndGetters)
{
	Vector3f v;
	v.setX(4.0f);
	v.setY(5.0f);
	v.setZ(6.0f);
	EXPECT_FLOAT_EQ(v.getX(), 4.0f);
	EXPECT_FLOAT_EQ(v.getY(), 5.0f);
	EXPECT_FLOAT_EQ(v.getZ(), 6.0f);
}

// Test length calculation
TEST(Vector3fTest, Length)
{
	Vector3f v(3.0f, 4.0f, 0.0f);
	EXPECT_FLOAT_EQ(v.length(), 5.0f);
}

// Test dot product
TEST(Vector3fTest, DotProduct)
{
	Vector3f v1(1.0f, 2.0f, 3.0f);
	Vector3f v2(4.0f, 5.0f, 6.0f);
	EXPECT_FLOAT_EQ(v1.dot(v2), 32.0f);
}

// Test normalization
TEST(Vector3fTest, Normalize)
{
	Vector3f v(3.0f, 4.0f, 0.0f);
	Vector3f normalized = v.normalize();
	EXPECT_FLOAT_EQ(normalized.length(), 1.0f);
}

// Test operators
TEST(Vector3fTest, Operators)
{
	Vector3f v1(1.0f, 2.0f, 3.0f);
	Vector3f v2(4.0f, 5.0f, 6.0f);
	Vector3f v3;

	// Test addition
	v3 = v1 + v2;
	EXPECT_FLOAT_EQ(v3.getX(), 5.0f);
	EXPECT_FLOAT_EQ(v3.getY(), 7.0f);
	EXPECT_FLOAT_EQ(v3.getZ(), 9.0f);

	// Test subtraction
	v3 = v1 - v2;
	EXPECT_FLOAT_EQ(v3.getX(), -3.0f);
	EXPECT_FLOAT_EQ(v3.getY(), -3.0f);
	EXPECT_FLOAT_EQ(v3.getZ(), -3.0f);

	// Test scalar multiplication
	v3 = v1 * 2.0f;
	EXPECT_FLOAT_EQ(v3.getX(), 2.0f);
	EXPECT_FLOAT_EQ(v3.getY(), 4.0f);
	EXPECT_FLOAT_EQ(v3.getZ(), 6.0f);

	// Test scalar division
	v3 = v1 / 2.0f;
	EXPECT_FLOAT_EQ(v3.getX(), 0.5f);
	EXPECT_FLOAT_EQ(v3.getY(), 1.0f);
	EXPECT_FLOAT_EQ(v3.getZ(), 1.5f);

	// Test cross product
	Vector3f crossProduct = v1.cross(v2);
	EXPECT_FLOAT_EQ(crossProduct.getX(), -3.0f);
	EXPECT_FLOAT_EQ(crossProduct.getY(), 6.0f);
	EXPECT_FLOAT_EQ(crossProduct.getZ(), -3.0f);
}

// Test rotate
TEST(Vector3fTest, Rotate)
{
	Vector3f v(1.0f, 1.0f, 1.0f);
	Vector3f axis(0.0f, 0.0f, 1.0f);
	float angle = 3.14159f / 2.0f;
	Vector3f rotated = v.rotate(angle, axis);
	EXPECT_NEAR(rotated.getX(), 0.97221213579177856f, 1e-6);
	EXPECT_NEAR(rotated.getY(), 1.0270364284515381f, 1e-6);
	EXPECT_NEAR(rotated.getZ(), 1.0f, 1e-6);
}
