/***************************************************************************
 * @file GameComponent.h
 *
 * @brief Declares the GameComponent class for game entities.
 *
 * This file contains the declaration of the GameComponent class, which
 * provides an interface for input handling, updating, and rendering of
 * game components.
 *
 ***************************************************************************/

#pragma once

#include <math/Transform.h>

#include <graphics/Shader.h>

/***************************************************************************
 * @class GameComponent
 *
 * @brief Abstract base class for game components.
 *
 * The GameComponent class provides an interface for handling input, updating
 * state, and rendering game components. It is intended to be inherited by
 * specific game components that implement these functionalities.
 *
 ***************************************************************************/
class GameComponent {
	Transform *transform = nullptr;

    public:
	//TODO: update docs
	/***************************************************************************
	 * @brief Pure virtual function to handle input.
	 *
	 * @param transform The Transform object representing the component's
	 *		  position and orientation.
	 ***************************************************************************/
	virtual void input(float delta = 0) = 0;

	/***************************************************************************
	 * @brief Pure virtual function to update the component.
	 *
	 * @param transform The Transform object representing the component's
	 *		  position and orientation.
	 ***************************************************************************/
	virtual void update(float delta = 0) = 0;

	/***************************************************************************
	 * @brief Pure virtual function to render the component.
	 *
	 * @param transform The Transform object representing the component's
	 *		  position and orientation.
	 * @param shader The Shader used for rendering.
	 ***************************************************************************/
	virtual void render(Shader &shader) = 0;

	/***************************************************************************
	 * @brief Virtual destructor.
	 *
	 * The destructor is virtual to ensure proper cleanup of derived class
	 * instances.
	 ***************************************************************************/
	virtual ~GameComponent() = default;

	// TODO: comments
	virtual void add_to_rendering_engine(bool id = 0) {};

	Transform *get_parent_transform() const noexcept
	{
		return transform;
	}

	void set_parent_transform(Transform *transform)
	{
		this->transform = transform;
	}
};
