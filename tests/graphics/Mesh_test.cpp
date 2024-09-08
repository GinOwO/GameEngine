#include <gtest/gtest.h>
#include <graphics/Mesh.h>
#include <graphics/Vertex.h>

class MeshTest : public ::testing::Test {
    protected:
	Mesh mesh;
	std::vector<Vertex> vertices;
	std::vector<int> indices;

	void SetUp() override
	{
		// Code here will run before each test
	}

	void TearDown() override
	{
		// Code here will run after each test
	}
};

TEST_F(MeshTest, DefaultConstructor)
{
	EXPECT_EQ(mesh.get_material().get_color(), Vector3f(0.0f, 0.0f, 0.0f));
}

TEST_F(MeshTest, ParameterizedConstructor)
{
	// Add vertices and indices to test
	Mesh customMesh(vertices, indices);
	EXPECT_EQ(customMesh.get_material().get_color(),
		  Vector3f(0.0f, 0.0f, 0.0f));
}

TEST_F(MeshTest, AddVertices)
{
	mesh.add_vertices(vertices, indices);
	// Check if vertices and indices were added correctly
}

TEST_F(MeshTest, DrawMesh)
{
	// Mock OpenGL calls or check if draw function behaves correctly
}

TEST_F(MeshTest, DeleteMesh)
{
	mesh.delete_mesh();
	// Check if resources were deleted correctly
}
