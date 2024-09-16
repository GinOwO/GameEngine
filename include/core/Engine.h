/***************************************************************************
 * @file Engine.h
 *
 * @brief Declares the Engine class, including its public and private methods
 *        and member variables.
 *
 * This file contains the declaration of the Engine class, which manages the
 * main game loop, the window, and the rendering engine. It includes methods
 * to start, stop, and clean up the engine, as well as access to the window.
 *
 ***************************************************************************/

#pragma once

#include <core/Input.h>
#include <core/Window.h>

#include <graphics/RenderingEngine.h>

#include <components/Game.h>

#include <string>

/***************************************************************************
 * @class Engine
 *
 * @brief Manages the main game loop, window, and rendering engine.
 *
 * The Engine class controls the game's execution flow, including the main
 * loop, window management, and rendering. It provides methods to start,
 * stop, and clean up the engine, and access the window object.
 *
 ***************************************************************************/
class Engine {
    private:
	/***************************************************************************
	 * @brief Static flag indicating if the Engine has been created.
	 ***************************************************************************/
	static bool created;

	/***************************************************************************
	 * @brief Frame cap for limiting the frame rate.
	 ***************************************************************************/
	double FRAME_CAP = 1000.0;

	/***************************************************************************
	 * @brief Reference to the Window object associated with the Engine.
	 ***************************************************************************/
	Window &window;

	/***************************************************************************
	 * @brief Flag indicating if the engine is currently running.
	 ***************************************************************************/
	bool running;

	/***************************************************************************
	 * @brief The main loop of the engine.
	 *
	 * This method contains the core logic for running the game loop and
	 * updating the engine's state.
	 ***************************************************************************/
	void run();

    public:
	/***************************************************************************
	 * @brief Constructs an Engine object.
	 *
	 * Initializes the engine but does not start it.
	 ***************************************************************************/
	Engine();

	/***************************************************************************
	 * @brief Destructs the Engine object.
	 *
	 * Cleans up resources when the engine is destroyed.
	 ***************************************************************************/
	~Engine();

	/***************************************************************************
	 * @brief Starts the engine.
	 *
	 * Begins the main game loop and initializes necessary components.
	 ***************************************************************************/
	void start();

	/***************************************************************************
	 * @brief Stops the engine.
	 *
	 * Ends the main game loop and initiates cleanup procedures.
	 ***************************************************************************/
	void stop();

	/***************************************************************************
	 * @brief Cleans up the engine's resources.
	 *
	 * Performs necessary cleanup operations to release resources.
	 ***************************************************************************/
	void cleanup();

	/***************************************************************************
	 * @brief Gets a reference to the Window object.
	 *
	 * @return Reference to the Window object associated with the Engine.
	 ***************************************************************************/
	Window &get_window() const noexcept;
};
