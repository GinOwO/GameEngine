#include <gtest/gtest.h>
#include <math/Vector2f.h> // Include your Vector2f header here

// Test the default constructor
TEST(Vector2fTest, DefaultConstructor)
{
	Vector2f vec;
	EXPECT_FLOAT_EQ(vec.getX(), 0.0f);
	EXPECT_FLOAT_EQ(vec.getY(), 0.0f);
}

// Test the parameterized constructor
TEST(Vector2fTest, ParameterizedConstructor)
{
	Vector2f vec(3.0f, 4.0f);
	EXPECT_FLOAT_EQ(vec.getX(), 3.0f);
	EXPECT_FLOAT_EQ(vec.getY(), 4.0f);
}

// Test the set and get functions
TEST(Vector2fTest, SettersAndGetters)
{
	Vector2f vec;
	vec.setX(5.0f);
	vec.setY(6.0f);
	EXPECT_FLOAT_EQ(vec.getX(), 5.0f);
	EXPECT_FLOAT_EQ(vec.getY(), 6.0f);
}

// Test the length function
TEST(Vector2fTest, Length)
{
	Vector2f vec(3.0f, 4.0f);
	EXPECT_FLOAT_EQ(vec.length(), 5.0f); // sqrt(3^2 + 4^2) = 5
}

// Test the dot product function
TEST(Vector2fTest, DotProduct)
{
	Vector2f vec1(1.0f, 2.0f);
	Vector2f vec2(2.0f, 3.0f);
	EXPECT_FLOAT_EQ(vec1.dot(vec2), 8.0f); // 1*2 + 2*3 = 8
}

// Test the normalize function
TEST(Vector2fTest, Normalize)
{
	Vector2f vec(3.0f, 4.0f);
	Vector2f normalized = vec.normalize();
	EXPECT_FLOAT_EQ(normalized.length(), 1.0f);
}

// Test arithmetic operators
TEST(Vector2fTest, ArithmeticOperators)
{
	Vector2f vec1(1.0f, 2.0f);
	Vector2f vec2(2.0f, 3.0f);

	Vector2f sum = vec1 + vec2;
	EXPECT_FLOAT_EQ(sum.getX(), 3.0f);
	EXPECT_FLOAT_EQ(sum.getY(), 5.0f);

	Vector2f diff = vec1 - vec2;
	EXPECT_FLOAT_EQ(diff.getX(), -1.0f);
	EXPECT_FLOAT_EQ(diff.getY(), -1.0f);

	Vector2f product = vec1 * 2.0f;
	EXPECT_FLOAT_EQ(product.getX(), 2.0f);
	EXPECT_FLOAT_EQ(product.getY(), 4.0f);

	Vector2f quotient = vec1 / 2.0f;
	EXPECT_FLOAT_EQ(quotient.getX(), 0.5f);
	EXPECT_FLOAT_EQ(quotient.getY(), 1.0f);
}

// Test compound assignment operators
TEST(Vector2fTest, CompoundAssignmentOperators)
{
	Vector2f vec(1.0f, 2.0f);

	vec += Vector2f(2.0f, 3.0f);
	EXPECT_FLOAT_EQ(vec.getX(), 3.0f);
	EXPECT_FLOAT_EQ(vec.getY(), 5.0f);

	vec -= Vector2f(1.0f, 1.0f);
	EXPECT_FLOAT_EQ(vec.getX(), 2.0f);
	EXPECT_FLOAT_EQ(vec.getY(), 4.0f);

	vec *= 2.0f;
	EXPECT_FLOAT_EQ(vec.getX(), 4.0f);
	EXPECT_FLOAT_EQ(vec.getY(), 8.0f);

	vec /= 2.0f;
	EXPECT_FLOAT_EQ(vec.getX(), 2.0f);
	EXPECT_FLOAT_EQ(vec.getY(), 4.0f);
}

// Test rotation function
TEST(Vector2fTest, Rotation)
{
	Vector2f vec(1.0f, 0.0f);
	Vector2f rotated = vec.rotate(90.0f);
	EXPECT_NEAR(rotated.getX(), 0.0f, 1e-5);
	EXPECT_NEAR(rotated.getY(), 1.0f, 1e-5);
}
