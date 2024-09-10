#include <game/GameObject.h>

GameObject::GameObject(Transform &transform)
	: children()
	, components()
	, transform(transform)
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

void GameObject::render()
{
	for (GameComponent *component : components) {
		component->render(transform);
	}

	for (GameObject *child : children) {
		child->render();
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