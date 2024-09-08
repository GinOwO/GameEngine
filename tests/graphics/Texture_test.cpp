#include <gtest/gtest.h>
#include <graphics/Texture.h>

class TextureTest : public ::testing::Test {
    protected:
	Texture texture;
	GLuint textureID = 1; // Mock texture ID

	void SetUp() override
	{
		// Initialize texture with a mock ID
		texture = Texture(textureID);
	}

	void TearDown() override
	{
		// Code here will run after each test
	}
};

TEST_F(TextureTest, DefaultConstructor)
{
	Texture defaultTexture;
	EXPECT_EQ(defaultTexture.get_id(), 0);
}

TEST_F(TextureTest, ParameterizedConstructor)
{
	EXPECT_EQ(texture.get_id(), textureID);
}

TEST_F(TextureTest, BindTexture)
{
	// Mock the bind function behavior
	// You may need to use a mock framework or check OpenGL state changes here
}
