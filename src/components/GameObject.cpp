#include <components/GameObject.h>

#include <math/Transform.h>

#include <graphics/Shader.h>

#include <components/SharedGlobals.h>
#include <components/GameComponent.h>

#include <vector>

/***************************************************************************
 * @brief Constructs a GameObject with default initialization.
 ***************************************************************************/
GameObject::GameObject()
	: children()
	, components()
	, transform()
{
}

/***************************************************************************
 * @brief Processes input for this GameObject and its children.
 *
 * Calls the input function for each component with the GameObject's 
 * transform and recursively processes input for each child GameObject.
 ***************************************************************************/
void GameObject::input()
{
	for (GameComponent *component : components) {
		component->input();
	}

	for (GameObject *child : children) {
		child->input();
	}
}

/***************************************************************************
 * @brief Updates this GameObject and its children.
 *
 * Calls the update function for each component with the GameObject's 
 * transform and recursively updates each child GameObject.
 ***************************************************************************/
void GameObject::update()
{
	for (GameComponent *component : components) {
		component->update();
	}

	for (GameObject *child : children) {
		child->update();
	}
}

/***************************************************************************
 * @brief Renders this GameObject and its children using the specified shader.
 *
 * Calls the render function for each component with the GameObject's 
 * transform and the given shader, and recursively renders each child 
 * GameObject.
 *
 * @param shader The shader to use for rendering.
 ***************************************************************************/
void GameObject::render(Shader &shader)
{
	for (GameComponent *component : components) {
		component->render(shader);
	}

	for (GameObject *child : children) {
		child->render(shader);
	}
}

//TODO:comments
void GameObject::add_to_rendering_engine()
{
	for (GameComponent *component : components) {
		component->add_to_rendering_engine();
	}

	for (GameObject *child : children) {
		child->add_to_rendering_engine();
	}
}

GameObject::~GameObject()
{
	for (GameComponent *obj : components) {
		delete obj;
	}

	for (GameObject *obj : children) {
		delete obj;
	}
}

/***************************************************************************
 * @brief Adds a child GameObject to this GameObject.
 *
 * @param obj A pointer to the child GameObject to add.
 ***************************************************************************/
void GameObject::add_child(GameObject *obj)
{
	children.push_back(obj);
}

/***************************************************************************
 * @brief Adds a component to this GameObject.
 *
 * @param obj A pointer to the GameComponent to add.
 ***************************************************************************/
void GameObject::add_component(GameComponent *obj)
{
	obj->set_parent_transform(&transform);
	components.push_back(obj);
}
