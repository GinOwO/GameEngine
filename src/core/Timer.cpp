#include <core/Timer.h>

#include <chrono>

/***************************************************************************
 * @brief Gets the singleton instance of the Timer class.
 *
 * @return A reference to the Timer instance.
 ***************************************************************************/
Timer &Timer::get_instance()
{
	static Timer instance;
	return instance;
}

/***************************************************************************
 * @brief Constructs a Timer object and initializes member variables.
 ***************************************************************************/
Timer::Timer()
	: last_time(std::chrono::high_resolution_clock::now())
{
}

/***************************************************************************
 * @brief Resets the timer.
 *
 * Updates the last recorded time and resets the passed time and delta time.
 ***************************************************************************/
void Timer::reset()
{
	last_time = std::chrono::high_resolution_clock::now();
	passed_time = 0.0;
	delta_time = 0.0;
}

/***************************************************************************
 * @brief Updates the delta time.
 *
 * Calculates the time elapsed since the last update and updates the last
 * recorded time.
 ***************************************************************************/
void Timer::update_delta_time() noexcept
{
	auto current_time = std::chrono::high_resolution_clock::now();
	delta_time =
		std::chrono::duration<double>(current_time - last_time).count();
	last_time = current_time;
}

/***************************************************************************
 * @brief Gets the time elapsed since the last update.
 *
 * @return The delta time in seconds.
 ***************************************************************************/
double Timer::get_delta_time() const noexcept
{
	return delta_time;
}

/***************************************************************************
 * @brief Checks if enough time has passed to render a new frame.
 *
 * Updates the elapsed time and determines if the frame rendering interval
 * has been reached.
 *
 * @param FRAME_TIME The time interval required for rendering a frame.
 * @return True if a new frame should be rendered, false otherwise.
 ***************************************************************************/
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
