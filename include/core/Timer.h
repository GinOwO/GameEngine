#pragma once

#include <chrono>

class Timer {
    public:
	Timer();

	void reset();
	void update_delta_time() noexcept;
	double get_delta_time() const noexcept;
	bool can_render_frame(const double FRAME_TIME) noexcept;

    private:
	std::chrono::high_resolution_clock::time_point last_time;
	double delta_time = 0.0;
	double passed_time = 0.0;
};
