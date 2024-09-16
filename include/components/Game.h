/***************************************************************************
 * @file Game.h
 *
 * @brief Declares the Game class for managing game logic and interactions.
 *
 * This file contains the declaration of the Game class, which provides
 * methods for initializing, updating, and rendering game objects.
 *
 ***************************************************************************/

#pragma once

#include <graphics/Shader.h>

#include <components/GameObject.h>

/***************************************************************************
 * @class Game
 *
 * @brief Abstract class for managing game logic and interactions.
 *
 * The Game class provides an interface for initializing, updating, and
 * rendering game objects. It manages a root game object and delegates
 * calls to this object.
 *
 ***************************************************************************/
class Game {
    private:
	/***************************************************************************
	 * @brief Pointer to the root GameObject in the scene.
	 ***************************************************************************/
	GameObject *root = nullptr;

    public:
	// TODO: comments
	~Game()
	{
		delete root;
	}
	/***************************************************************************
	 * @brief Pure virtual function to initialize the game.
	 *
	 * This function must be implemented by derived classes to perform game
	 * initialization.
	 ***************************************************************************/
	virtual void init() = 0;

	/***************************************************************************
	 * @brief Calls the input method of the root GameObject.
	 *
	 * This method is used to handle input events for the game.
	 ***************************************************************************/
	void input()
	{
		get_root_object()->input();
	};

	/***************************************************************************
	 * @brief Calls the update method of the root GameObject.
	 *
	 * This method is used to update the game state.
	 ***************************************************************************/
	void update()
	{
		get_root_object()->update();
	};

	/***************************************************************************
	 * @brief Calls the render method of the root GameObject.
	 *
	 * @param shader The Shader used for rendering.
	 ***************************************************************************/
	void render(Shader &shader)
	{
		get_root_object()->render(shader);
	};

	/***************************************************************************
	 * @brief Gets the root GameObject, creating it if necessary.
	 *
	 * @return Pointer to the root GameObject.
	 ***************************************************************************/
	GameObject *get_root_object() noexcept
	{
		if (root == nullptr) {
			root = new GameObject();
		}
		return root;
	}
};
