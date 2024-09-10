#include <game/GameObject.h>

#include <math/Transform.h>

#include <graphics/Shader.h>

#include <game/GameComponent.h>

#include <vector>

GameObject::GameObject()
	: children()
	, components()
	, transform()
{
}

void GameObject::input()
{
	for (GameComponent *component : components) {
		component->input(transform);
	}

	for (GameObject *child : children) {
		child->input();
	}
}

void GameObject::update()
{
	for (GameComponent *component : components) {
		component->update(transform);
	}

	for (GameObject *child : children) {
		child->update();
	}
}

void GameObject::render(Shader &shader)
{
	for (GameComponent *component : components) {
		component->render(transform, shader);
	}

	for (GameObject *child : children) {
		child->render(shader);
	}
}

void GameObject::add_child(GameObject *obj)
{
	children.push_back(obj);
}

void GameObject::add_component(GameComponent *obj)
{
	components.push_back(obj);
}