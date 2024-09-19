/***************************************************************************
 * @file Timer.h
 *
 * @brief Declares the Timer class for measuring elapsed time and managing
 *	frame rate.
 *
 * This file contains the declaration of the Timer class, which provides
 * functionality for measuring time intervals, updating delta time, and
 * managing frame rendering based on elapsed time.
 *
 ***************************************************************************/

#pragma once

#include <chrono>

/***************************************************************************
 * @class Timer
 *
 * @brief Singleton class for measuring time and managing frame rate.
 *
 * The Timer class provides methods for measuring elapsed time, updating
 * delta time, and determining if a frame can be rendered based on a
 * specified frame time.
 *
 ***************************************************************************/
class Timer {
    public:
	/***************************************************************************
	 * @brief Deleted copy constructor to prevent copying.
	 ***************************************************************************/
	Timer(const Timer &) = delete;

	/***************************************************************************
	 * @brief Deleted copy assignment operator to prevent copying.
	 ***************************************************************************/
	Timer &operator=(const Timer &) = delete;

	/***************************************************************************
	 * @brief Gets the singleton instance of the Timer class.
	 *
	 * @return Reference to the singleton Timer instance.
	 ***************************************************************************/
	static Timer &get_instance();

    private:
	/***************************************************************************
	 * @brief Private constructor to prevent instantiation outside of the class.
	 ***************************************************************************/
	Timer();

	/***************************************************************************
	 * @brief Time point representing the last update time.
	 ***************************************************************************/
	std::chrono::high_resolution_clock::time_point last_time;

	/***************************************************************************
	 * @brief Time elapsed since the last update.
	 ***************************************************************************/
	double delta_time = 0.0;

	/***************************************************************************
	 * @brief Total time passed since the timer was started.
	 ***************************************************************************/
	double passed_time = 0.0;

    public:
	/***************************************************************************
	 * @brief Resets the timer to the current time.
	 ***************************************************************************/
	void reset();

	/***************************************************************************
	 * @brief Updates the delta time based on the elapsed time since the last update.
	 *
	 * This method calculates the time difference between the current time and
	 * the last recorded time, and updates the delta_time and passed_time
	 * accordingly.
	 ***************************************************************************/
	void update_delta_time() noexcept;

	/***************************************************************************
	 * @brief Gets the time elapsed since the last update.
	 *
	 * @return The delta time in seconds.
	 ***************************************************************************/
	double get_delta_time() const noexcept;

	/***************************************************************************
	 * @brief Determines if enough time has passed to render a new frame.
	 *
	 * @param FRAME_TIME The time interval required for rendering a frame.
	 * @return True if the frame can be rendered, false otherwise.
	 ***************************************************************************/
	bool can_render_frame(const double FRAME_TIME) noexcept;
};
