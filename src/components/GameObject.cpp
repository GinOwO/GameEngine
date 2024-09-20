#include <components/GameObject.h>

#include <math/Transform.h>

#include <graphics/Shader.h>

#include <components/SharedGlobals.h>
#include <components/GameComponent.h>

#include <vector>

GameObject::GameObject()
	: children()
	, components()
	, transform()
{
}

void GameObject::input(float delta)
{
	transform.update();
	for (GameComponent *component : components) {
		component->input(delta);
	}

	for (GameObject *child : children) {
		child->input(delta);
	}
}

void GameObject::update(float delta)
{
	for (GameComponent *component : components) {
		component->update(delta);
	}

	for (GameObject *child : children) {
		child->update(delta);
	}
}

void GameObject::render(Shader &shader)
{
	for (GameComponent *component : components) {
		component->render(shader);
	}

	for (GameObject *child : children) {
		child->render(shader);
	}
}

void GameObject::reset()
{
	for (GameComponent *component : components) {
		component->reset();
	}

	for (GameObject *child : children) {
		child->reset();
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

GameObject *GameObject::add_child(GameObject *obj)
{
	obj->transform.parent = &transform;
	children.push_back(obj);
	return this;
}

GameObject *GameObject::add_component(GameComponent *obj)
{
	obj->set_parent_transform(&transform);
	components.push_back(obj);
	return this;
}
