#include <gtest/gtest.h>
#include <core/Timer.h>

class TimerTest : public ::testing::Test {
    protected:
	Timer timer;

	void SetUp() override
	{
		// Initialize or set up anything specific to Timer if needed
	}
};

TEST_F(TimerTest, DefaultConstructor)
{
	EXPECT_NO_THROW(Timer());
}

TEST_F(TimerTest, Reset)
{
	EXPECT_NO_THROW(timer.reset());
}

TEST_F(TimerTest, DeltaTime)
{
	timer.update_delta_time();
	EXPECT_NO_THROW(timer.get_delta_time());
}

TEST_F(TimerTest, CanRenderFrame)
{
	EXPECT_TRUE(timer.can_render_frame(16.67)); // assuming 60 FPS
}
