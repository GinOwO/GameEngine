/***************************************************************************
 * @file RenderingEngine.h
 *
 * @brief Declares the RenderingEngine class for managing rendering operations.
 *
 * This file contains the declaration of the RenderingEngine class, which
 * handles rendering operations, including clearing the screen, setting the
 * clear color, and rendering game objects. It uses a singleton pattern for
 * accessing the rendering engine instance.
 *
 ***************************************************************************/

#pragma once

#include <math/Vector3f.h>

#include <core/Camera.h>

#include <components/GameObject.h>

#include <vector>

/***************************************************************************
 * @class RenderingEngine
 *
 * @brief Manages rendering operations for the game engine.
 *
 * The RenderingEngine class is responsible for handling rendering operations,
 * including clearing the screen, setting the clear color, enabling or disabling
 * textures, and rendering game objects. It utilizes a singleton pattern to
 * ensure a single instance throughout the application.
 *
 ***************************************************************************/
class RenderingEngine {
    public:
	/***************************************************************************
	 * @brief Deleted copy constructor.
	 ***************************************************************************/
	RenderingEngine(const RenderingEngine &) = delete;

	/***************************************************************************
	 * @brief Deleted assignment operator.
	 ***************************************************************************/
	RenderingEngine &operator=(const RenderingEngine &) = delete;

	/***************************************************************************
	 * @brief Gets the singleton instance of the RenderingEngine.
	 *
	 * @return The singleton instance of the RenderingEngine.
	 ***************************************************************************/
	static RenderingEngine &get_instance();

    private:
	Camera &camera; /**< Reference to the Camera used for rendering. */

	/***************************************************************************
	 * @brief Sets the clear color for the rendering engine.
	 *
	 * @param color The color to use for clearing the screen.
	 ***************************************************************************/
	static void set_clear_color(const Vector3f &color);

	/***************************************************************************
	 * @brief Unbinds any currently bound textures.
	 ***************************************************************************/
	static void unbind_textures();

	/***************************************************************************
	 * @brief Enables or disables texture usage.
	 *
	 * @param enable Whether to enable or disable texture usage. Defaults to true.
	 ***************************************************************************/
	static void texture_enable(bool enable = true);

	/***************************************************************************
	 * @brief Clears the screen.
	 ***************************************************************************/
	static void clear_screen();

	/***************************************************************************
	 * @brief Constructs a RenderingEngine instance.
	 ***************************************************************************/
	RenderingEngine();

    public:
	/***************************************************************************
	 * @brief Handles input for rendering.
	 ***************************************************************************/
	void input();

	/***************************************************************************
	 * @brief Renders a game object.
	 *
	 * @param object The GameObject to render.
	 ***************************************************************************/
	void render(GameObject *object);
};
