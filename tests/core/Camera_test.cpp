#include <gtest/gtest.h>
#include <math/Vector3f.h>
#include <core/Camera.h>

class CameraTest : public ::testing::Test {
    protected:
	Camera camera;
	Vector3f default_position{ 0.0f, 0.0f, 0.0f };
	Vector3f default_forward{ 0.0f, 0.0f, 1.0f };
	Vector3f default_up{ 0.0f, 1.0f, 0.0f };

	void SetUp() override
	{
		camera = Camera(default_position, default_forward, default_up);
	}
};

TEST_F(CameraTest, DefaultConstructor)
{
	EXPECT_EQ(camera.get_position(), default_position);
	EXPECT_EQ(camera.get_forward(), default_forward);
	EXPECT_EQ(camera.get_up(), default_up);
}

TEST_F(CameraTest, SetPosition)
{
	Vector3f new_position{ 1.0f, 2.0f, 3.0f };
	camera.set_position(new_position);
	EXPECT_EQ(camera.get_position(), new_position);
}

TEST_F(CameraTest, SetForward)
{
	Vector3f new_forward{ 1.0f, 0.0f, 0.0f };
	camera.set_forward(new_forward);
	EXPECT_EQ(camera.get_forward(), new_forward);
}

TEST_F(CameraTest, SetUp)
{
	Vector3f new_up{ 0.0f, 1.0f, 1.0f };
	camera.set_up(new_up);
	EXPECT_EQ(camera.get_up(), new_up);
}

TEST_F(CameraTest, MoveCamera)
{
	Vector3f direction{ 1.0f, 0.0f, 0.0f };
	camera.move_camera(direction, 10.0f);
	EXPECT_EQ(camera.get_position(), Vector3f(10.0f, 0.0f, 0.0f));
}
