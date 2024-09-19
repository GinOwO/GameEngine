#include <gtest/gtest.h>
#include <math/Matrix4f.h>
#include <math/Vector3f.h>

class Matrix4fTest : public ::testing::Test {
    protected:
	Matrix4f m1;
	Matrix4f m2;

	void SetUp() override
	{
		m1 = Matrix4f::Identity_Matrix();
		m2 = Matrix4f::Identity_Matrix();
	}
};

TEST_F(Matrix4fTest, TestIdentityMatrix)
{
	Matrix4f identity = Matrix4f::Identity_Matrix();
	EXPECT_EQ(identity.get(0, 0), 1.0f);
	EXPECT_EQ(identity.get(1, 1), 1.0f);
	EXPECT_EQ(identity.get(2, 2), 1.0f);
	EXPECT_EQ(identity.get(3, 3), 1.0f);
}

TEST_F(Matrix4fTest, TestTranslationMatrix)
{
	Matrix4f translation = Matrix4f::Translation_Matrix(1.0f, 2.0f, 3.0f);
	EXPECT_EQ(translation.get(0, 3), 1.0f);
	EXPECT_EQ(translation.get(1, 3), 2.0f);
	EXPECT_EQ(translation.get(2, 3), 3.0f);
}

TEST_F(Matrix4fTest, TestRotationMatrix)
{
	Matrix4f rotation = Matrix4f::Rotation_Matrix(90.0f, 0.0f, 0.0f);
	EXPECT_NEAR(rotation.get(1, 1), 0.0f, 1e-5);
	EXPECT_NEAR(rotation.get(1, 2), -1.0f, 1e-5);
	EXPECT_NEAR(rotation.get(2, 1), 1.0f, 1e-5);
	EXPECT_NEAR(rotation.get(2, 2), 0.0f, 1e-5);
}

TEST_F(Matrix4fTest, TestScaleMatrix)
{
	Matrix4f scale = Matrix4f::Scale_Matrix(2.0f, 3.0f, 4.0f);
	EXPECT_EQ(scale.get(0, 0), 2.0f);
	EXPECT_EQ(scale.get(1, 1), 3.0f);
	EXPECT_EQ(scale.get(2, 2), 4.0f);
}

TEST_F(Matrix4fTest, TestMultiplication)
{
	Matrix4f result = m1 * m2;
	EXPECT_EQ(result.get(0, 0), 1.0f); // Identity matrix multiplication
}

TEST_F(Matrix4fTest, TestEquality)
{
	EXPECT_TRUE(m1 == m2);
}

TEST_F(Matrix4fTest, TestProjectionMatrix)
{
	Matrix4f projection = Matrix4f::Perspective_Matrix(
		1.22173f, 1920.0f / 1080.0f, 0.1f, 1000.0f);
	EXPECT_NEAR(projection.get(0, 0), 0.80333322286605835f, 1e-5);
	EXPECT_NEAR(projection.get(1, 1), 1.4281480312347412f, 1e-5);
}
