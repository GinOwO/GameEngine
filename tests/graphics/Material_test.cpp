#include <gtest/gtest.h>
#include <graphics/Material.h>

class MaterialTest : public ::testing::Test {
    protected:
	Texture texture;
	Vector3f color{ 1.0f, 1.0f, 1.0f };
	Material material;

	void SetUp() override
	{
		material = Material(texture, color);
	}

	void TearDown() override
	{
		// Code here will run after each test
	}
};

TEST_F(MaterialTest, DefaultConstructor)
{
	Material defaultMaterial;
	EXPECT_EQ(defaultMaterial.get_color(), Vector3f(0.0f, 0.0f, 0.0f));
}

TEST_F(MaterialTest, ParameterizedConstructor)
{
	EXPECT_EQ(material.get_color(), color);
	EXPECT_EQ(material.get_texture().get_id(), texture.get_id());
}

TEST_F(MaterialTest, SetColor)
{
	Vector3f newColor{ 0.5f, 0.5f, 0.5f };
	material.set_color(newColor);
	EXPECT_EQ(material.get_color(), newColor);
}

TEST_F(MaterialTest, SetTexture)
{
	Texture newTexture(2);
	material.set_texture(newTexture);
	EXPECT_EQ(material.get_texture().get_id(), newTexture.get_id());
}
