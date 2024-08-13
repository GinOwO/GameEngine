#include <Timer.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Timer::Timer()
{
	Timer::reset();
}

void Timer::reset()
{
	passed_time = 0.0;
	start_time = 0.0;
	last_time = 0.0;
}

void Timer::update_delta_time() noexcept
{
	this->start_time = glfwGetTime();
	this->delta_time = start_time - last_time;
	this->last_time = start_time;
}

double Timer::get_delta_time() const noexcept
{
	return this->delta_time;
}

bool Timer::can_render_frame(const double FRAME_TIME) noexcept
{
	this->update_delta_time();
	passed_time += this->get_delta_time();
	if (passed_time >= FRAME_TIME) {
		passed_time -= FRAME_TIME;
		return true;
	}
	return false;
}