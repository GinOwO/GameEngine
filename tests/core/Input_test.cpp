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

// Test mouse button press
TEST_F(InputTest, MouseButtonPress)
{
	input.mouse_button_callback(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
	EXPECT_TRUE(input.is_mouse_pressed(GLFW_MOUSE_BUTTON_LEFT));
	EXPECT_TRUE(input.is_mouse_down(GLFW_MOUSE_BUTTON_LEFT));
}

// Test mouse button release
TEST_F(InputTest, MouseButtonRelease)
{
	input.mouse_button_callback(GLFW_MOUSE_BUTTON_RIGHT, GLFW_RELEASE, 0);
	EXPECT_FALSE(input.is_mouse_pressed(GLFW_MOUSE_BUTTON_RIGHT));
	EXPECT_FALSE(input.is_mouse_down(GLFW_MOUSE_BUTTON_RIGHT));
	EXPECT_TRUE(input.is_mouse_up(GLFW_MOUSE_BUTTON_RIGHT));
}

// Test mouse movement callback
TEST_F(InputTest, MouseMovementCallback)
{
	input.mouse_motion_callback(100.0, 200.0);
	const double(*mouse_pos)[2] = input.get_mouse_pos();
	EXPECT_EQ(mouse_pos[0][0], 100.0);
	EXPECT_EQ(mouse_pos[0][1], 200.0);
}

// Test mouse scroll callback
TEST_F(InputTest, MouseScrollCallback)
{
	input.mouse_scroll_callback(10.0, -5.0);
	const double(*mouse_scroll)[2] = input.get_mouse_scroll();
	EXPECT_EQ(mouse_scroll[0][0], 10.0);
	EXPECT_EQ(mouse_scroll[0][1], -5.0);
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
