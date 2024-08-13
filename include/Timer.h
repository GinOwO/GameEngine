#pragma once

class Timer {
    private:
	double start_time;
	double last_time;
	double passed_time;
	double delta_time;
	void update_delta_time() noexcept;

    public:
	Timer();

	const double SECOND = 1e9;

	void reset();
	bool can_render_frame(const double FRAME_TIME) noexcept;

	double get_delta_time() const noexcept;
};