#include <gtest/gtest.h>
#include <math/Quaternion.h>
#include <math/Vector3f.h>

class QuaternionTest : public ::testing::Test {
    protected:
	Quaternion q1;
	Quaternion q2;
	Quaternion q3;

	void SetUp() override
	{
		q1 = Quaternion(1, 2, 3, 4);
		q2 = Quaternion(5, 6, 7, 8);
		q3 = Quaternion(0, 0, 0, 1); // Identity quaternion
	}
};

TEST_F(QuaternionTest, TestAddition)
{
	Quaternion result = q1 + q2;
	EXPECT_EQ(result.getX(), 6);
	EXPECT_EQ(result.getY(), 8);
	EXPECT_EQ(result.getZ(), 10);
	EXPECT_EQ(result.getW(), 12);
}

TEST_F(QuaternionTest, TestSubtraction)
{
	Quaternion result = q1 - q2;
	EXPECT_EQ(result.getX(), -4);
	EXPECT_EQ(result.getY(), -4);
	EXPECT_EQ(result.getZ(), -4);
	EXPECT_EQ(result.getW(), -4);
}

TEST_F(QuaternionTest, TestMultiplicationWithScalar)
{
	Quaternion result = q1 * 2.0f;
	EXPECT_EQ(result.getX(), 2);
	EXPECT_EQ(result.getY(), 4);
	EXPECT_EQ(result.getZ(), 6);
	EXPECT_EQ(result.getW(), 8);
}

TEST_F(QuaternionTest, TestNormalize)
{
	Quaternion normalized = q1.normalize();
	EXPECT_FLOAT_EQ(normalized.length(), 1.0f);
}

TEST_F(QuaternionTest, TestConjugate)
{
	Quaternion conj = q1.conjugate();
	EXPECT_EQ(conj.getX(), -1);
	EXPECT_EQ(conj.getY(), -2);
	EXPECT_EQ(conj.getZ(), -3);
	EXPECT_EQ(conj.getW(), 4);
}

TEST_F(QuaternionTest, TestMultiplicationWithQuaternion)
{
	Quaternion result = q1 * q3; // Multiplying by identity quaternion
	EXPECT_EQ(result.getX(), q1.getX());
	EXPECT_EQ(result.getY(), q1.getY());
	EXPECT_EQ(result.getZ(), q1.getZ());
	EXPECT_EQ(result.getW(), q1.getW());
}

TEST_F(QuaternionTest, TestEquality)
{
	Quaternion identical = Quaternion(1, 2, 3, 4);
	EXPECT_TRUE(q1 == identical);
}
