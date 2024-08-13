#pragma once

#include <Window.h>
#include <Input.h>

class Engine {
    private:
	double FRAME_CAP = 60.0;
	Window window;
	bool running;

	void run();
	void render();

    public:
	Engine();
	~Engine();
	void start();
	void stop();
	void cleanup();

	Window get_window() const noexcept;
};