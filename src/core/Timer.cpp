#include <core/Timer.h>

#include <chrono>

Timer &Timer::get_instance()
{
	static Timer instance;
	return instance;
}

Timer::Timer()
	: last_time(std::chrono::high_resolution_clock::now())
{
}

void Timer::reset()
{
	last_time = std::chrono::high_resolution_clock::now();
	passed_time = 0.0;
	delta_time = 0.0;
}

void Timer::update_delta_time() noexcept
{
	auto current_time = std::chrono::high_resolution_clock::now();
	delta_time =
		std::chrono::duration<double>(current_time - last_time).count();
	last_time = current_time;
}

double Timer::get_delta_time() const noexcept
{
	return delta_time;
}

bool Timer::can_render_frame(const double FRAME_TIME) noexcept
{
	update_delta_time();
	passed_time += delta_time;
	if (passed_time >= FRAME_TIME) {
		passed_time -= FRAME_TIME;
		return true;
	}
	return false;
}