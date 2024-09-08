#include <gtest/gtest.h>
#include <graphics/Shader.h>

class ShaderTest : public ::testing::Test {
    protected:
	Shader shader;
	Shader customShader{ "vertex_shader.glsl", "fragment_shader.glsl" };

	void SetUp() override
	{
		// Code here will run before each test
	}

	void TearDown() override
	{
		// Code here will run after each test
	}
};

TEST_F(ShaderTest, DefaultConstructor)
{
	EXPECT_NE(shader.get_program(), 0);
}

TEST_F(ShaderTest, ParameterizedConstructor)
{
	EXPECT_NE(customShader.get_program(), 0);
}

TEST_F(ShaderTest, AddUniform)
{
	shader.add_uniform("testUniform");
	EXPECT_NE(shader.get_uniform("testUniform"), 0);
}

TEST_F(ShaderTest, SetUniformInt)
{
	shader.set_uniform("testUniformInt", 1);
	// Check if uniform was set correctly
}

TEST_F(ShaderTest, SetUniformFloat)
{
	shader.set_uniform("testUniformFloat", 1.0f);
	// Check if uniform was set correctly
}

TEST_F(ShaderTest, SetUniformVector3f)
{
	Vector3f vec{ 1.0f, 1.0f, 1.0f };
	shader.set_uniform("testUniformVec3", vec);
	// Check if uniform was set correctly
}

TEST_F(ShaderTest, SetUniformMatrix4f)
{
	Matrix4f mat;
	shader.set_uniform("testUniformMatrix", mat);
	// Check if uniform was set correctly
}
