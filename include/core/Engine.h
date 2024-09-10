#pragma once

#include <core/Window.h>
#include <core/Input.h>
#include <game/Game.h>

#include <string>

class Engine {
    private:
	static bool created;

	double FRAME_CAP = 1000.0;
	Window &window;
	bool running;

	void run();

    public:
	Engine();
	~Engine();
	void start();
	void stop();
	void cleanup();

	Window &get_window() const noexcept;
};