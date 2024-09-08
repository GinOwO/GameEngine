#include <gtest/gtest.h>
#include <graphics/BasicShader.h>

class BasicShaderTest : public ::testing::Test {
    protected:
	BasicShader shader;
	Matrix4f world_matrix;
	Matrix4f projected_matrix;
	Material material;

	void SetUp() override
	{
		// Code here will run before each test
	}

	void TearDown() override
	{
		// Code here will run after each test
	}
};

TEST_F(BasicShaderTest, DefaultConstructor)
{
	EXPECT_NE(shader.get_program(), 0);
}

TEST_F(BasicShaderTest, ParameterizedConstructor)
{
	BasicShader customShader("vertex_shader.glsl", "fragment_shader.glsl");
	EXPECT_NE(customShader.get_program(), 0);
}

TEST_F(BasicShaderTest, UpdateUniforms)
{
	shader.update_uniforms(world_matrix, projected_matrix, material);
	// Check if uniforms were updated correctly
}
