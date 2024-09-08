#include <gtest/gtest.h>
#include <core/RenderUtil.h>

class RenderUtilTest : public ::testing::Test {
    protected:
	void SetUp() override
	{
		// Initialize or set up anything specific to RenderUtil if needed
	}
};

TEST_F(RenderUtilTest, ClearScreen)
{
	EXPECT_NO_THROW(RenderUtil::clear_screen());
}

TEST_F(RenderUtilTest, SetClearColor)
{
	Vector3f color{ 0.1f, 0.2f, 0.3f };
	EXPECT_NO_THROW(RenderUtil::set_clear_color(color));
}
