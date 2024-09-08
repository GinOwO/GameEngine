#include <gtest/gtest.h>
#include <graphics/Vertex.h>
#include <math/Vector3f.h>
#include <math/Vector2f.h>

class VertexTest : public ::testing::Test {
    protected:
	Vector3f pos{ 1.0f, 2.0f, 3.0f };
	Vector2f texCoord{ 0.5f, 0.5f };
	Vector3f normal{ 0.0f, 1.0f, 0.0f };

	Vertex vertex1;
	Vertex vertex2{ pos };
	Vertex vertex3{ pos, texCoord };
	Vertex vertex4{ pos, texCoord, normal };

	void SetUp() override
	{
		// Code here will run before each test
	}

	void TearDown() override
	{
		// Code here will run after each test
	}
};

TEST_F(VertexTest, DefaultConstructor)
{
	EXPECT_EQ(vertex1.get_pos(), Vector3f(0.0f, 0.0f, 0.0f));
	EXPECT_EQ(vertex1.get_texCoord(), Vector2f(0.0f, 0.0f));
	EXPECT_EQ(vertex1.get_normal(), Vector3f(0.0f, 0.0f, 0.0f));
}

TEST_F(VertexTest, ConstructorWithPosition)
{
	EXPECT_EQ(vertex2.get_pos(), pos);
	EXPECT_EQ(vertex2.get_texCoord(), Vector2f(0.0f, 0.0f));
	EXPECT_EQ(vertex2.get_normal(), Vector3f(0.0f, 0.0f, 0.0f));
}

TEST_F(VertexTest, ConstructorWithPositionAndTexCoord)
{
	EXPECT_EQ(vertex3.get_pos(), pos);
	EXPECT_EQ(vertex3.get_texCoord(), texCoord);
	EXPECT_EQ(vertex3.get_normal(), Vector3f(0.0f, 0.0f, 0.0f));
}

TEST_F(VertexTest, ConstructorWithAllParameters)
{
	EXPECT_EQ(vertex4.get_pos(), pos);
	EXPECT_EQ(vertex4.get_texCoord(), texCoord);
	EXPECT_EQ(vertex4.get_normal(), normal);
}

TEST_F(VertexTest, SetGetPosition)
{
	Vector3f newPos{ 4.0f, 5.0f, 6.0f };
	vertex1.set_pos(newPos);
	EXPECT_EQ(vertex1.get_pos(), newPos);
}

TEST_F(VertexTest, SetGetNormal)
{
	Vector3f newNormal{ 1.0f, 0.0f, 0.0f };
	vertex1.set_normal(newNormal);
	EXPECT_EQ(vertex1.get_normal(), newNormal);
}

TEST_F(VertexTest, SetGetTexCoord)
{
	Vector2f newTexCoord{ 0.75f, 0.75f };
	vertex1.set_texCoord(newTexCoord);
	EXPECT_EQ(vertex1.get_texCoord(), newTexCoord);
}
