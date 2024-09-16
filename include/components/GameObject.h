/***************************************************************************
 * @file GameObject.h
 *
 * @brief Declares the GameObject class for managing game entities and components.
 *
 * This file contains the declaration of the GameObject class, which
 * manages a collection of child objects and components. It provides methods
 * for handling input, updating, and rendering game objects.
 *
 ***************************************************************************/

#pragma once

#include <math/Transform.h>

#include <graphics/Shader.h>

#include <components/GameComponent.h>

#include <vector>

/***************************************************************************
 * @class GameObject
 *
 * @brief Manages game entities and their components.
 *
 * The GameObject class represents a game entity that can contain other
 * game objects (children) and components. It provides methods for handling
 * input, updating, and rendering. Each GameObject has a Transform that
 * represents its position, orientation, and scale in the game world.
 *
 ***************************************************************************/
class GameObject {
    private:
	/***************************************************************************
	 * @brief List of child GameObjects.
	 ***************************************************************************/
	std::vector<GameObject *> children;

	/***************************************************************************
	 * @brief List of components attached to this GameObject.
	 ***************************************************************************/
	std::vector<GameComponent *> components;

    public:
	// TODO: Comment
	~GameObject();

	/***************************************************************************
	 * @brief The Transform of this GameObject.
	 ***************************************************************************/
	Transform transform;

	/***************************************************************************
	 * @brief Constructs a GameObject.
	 ***************************************************************************/
	GameObject();

	/***************************************************************************
	 * @brief Calls the input method for this GameObject and its components.
	 ***************************************************************************/
	void input();

	/***************************************************************************
	 * @brief Calls the update method for this GameObject and its components.
	 ***************************************************************************/
	void update();

	/***************************************************************************
	 * @brief Calls the render method for this GameObject and its components.
	 *
	 * @param shader The Shader used for rendering.
	 ***************************************************************************/
	void render(Shader &shader);

	/***************************************************************************
	 * @brief Adds a child GameObject to this GameObject.
	 *
	 * @param obj Pointer to the GameObject to be added as a child.
	 ***************************************************************************/
	void add_child(GameObject *obj);

	/***************************************************************************
	 * @brief Adds a component to this GameObject.
	 *
	 * @param obj Pointer to the GameComponent to be added.
	 ***************************************************************************/
	void add_component(GameComponent *obj);

	// TODO: Comments
	void add_to_rendering_engine();
};
