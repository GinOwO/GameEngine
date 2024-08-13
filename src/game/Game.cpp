#include <game/Game.h>

#include <Mesh.h>

Game::Game(Input &input_)
	: input_handler(input_)
{
	vertices = { Vertex(Vector3f(0.0, 0.5, 0.0)),
		     Vertex(Vector3f(-0.5, -0.5, 0.0)),
		     Vertex(Vector3f(0.5, -0.5, 0.0)) };

	mesh.add_vertices(vertices);
}

void Game::input()
{
}

void Game::update()
{
}

void Game::render()
{
	mesh.draw();
}