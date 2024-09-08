#include <gtest/gtest.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <core/Input.h>

class InputTest : public ::testing::Test {
    protected:
	Input input;

	void SetUp() override
	{
		// Initialize or set up anything specific to Input if needed
	}
};

// Test key press registration
TEST_F(InputTest, KeyPress)
{
	input.key_callback(GLFW_KEY_A, 0, GLFW_PRESS, 0);
	EXPECT_TRUE(input.is_key_pressed(GLFW_KEY_A));
	EXPECT_TRUE(input.is_key_down(GLFW_KEY_A));
}

// Test key release
TEST_F(InputTest, KeyRelease)
{
	input.key_callback(GLFW_KEY_B, 0, GLFW_RELEASE, 0);
	EXPECT_FALSE(input.is_key_pressed(GLFW_KEY_B));
	EXPECT_FALSE(input.is_key_down(GLFW_KEY_B));
	EXPECT_TRUE(input.is_key_up(GLFW_KEY_B));
}

// Test mouse button release
TEST_F(InputTest, MouseButtonRelease)
{
	input.mouse_button_callback(GLFW_MOUSE_BUTTON_RIGHT, GLFW_RELEASE, 0);
	EXPECT_FALSE(input.is_mouse_pressed(GLFW_MOUSE_BUTTON_RIGHT));
	EXPECT_FALSE(input.is_mouse_down(GLFW_MOUSE_BUTTON_RIGHT));
	EXPECT_TRUE(input.is_mouse_up(GLFW_MOUSE_BUTTON_RIGHT));
}

// Test key down and key up
TEST_F(InputTest, KeyDownAndUp)
{
	input.key_callback(GLFW_KEY_C, 0, GLFW_PRESS, 0);
	EXPECT_TRUE(input.is_key_down(GLFW_KEY_C));

	input.key_callback(GLFW_KEY_C, 0, GLFW_RELEASE, 0);
	EXPECT_TRUE(input.is_key_up(GLFW_KEY_C));
	EXPECT_FALSE(input.is_key_down(GLFW_KEY_C));
}

// Test mouse scroll delta
TEST_F(InputTest, MouseScrollDelta)
{
	input.mouse_scroll_callback(0.0, 0.0);
	const double *scroll_delta = input.get_mouse_scroll_delta();
	EXPECT_EQ(scroll_delta[0], 0.0);
	EXPECT_EQ(scroll_delta[1], 0.0);
}
