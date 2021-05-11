#include "Engine.h"

Engine::Engine() = default;

Engine::~Engine() = default;

void Engine::Start(sf::RenderWindow* window)
{
	quit = false;
	this->window = window;

	// run the program as long as the window is open
	while (window->isOpen()) {
		Update();
	}
}

void Engine::AddSystem(ECS::EntitySystem* system)
{
	world->registerSystem(system);
	world->enableSystem(system);
}

Engine& Engine::GetInstance()
{
	static Engine instance;

	return instance;
}

void Engine::Update()
{
	sf::Event event;

	while (window->pollEvent(event)) {
		// close requested event

		if (event.type == sf::Event::Closed) {
			window->close();
			break;
		}

	}
	world->tick(10);
}
