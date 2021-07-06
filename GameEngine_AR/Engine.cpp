#include "Engine.h"

Engine::Engine() = default;

Engine::~Engine() = default;

void Engine::Start(sf::RenderWindow* window)
{
	quit = false;
	this->window = window;
	mainCamera = MainCamera(sf::Vector2f(
		this->window->getSize().x / 2, this->window->getSize().y / 2
	));
	menu = PauseMenu(window);

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
		menu.Update(event, 10.0f, window);
	}
	world->tick(10.0f);
	mainCamera.Update(world, 10.0f, window);
	if (States::getPause()) {
		OnGameInactiveState();
		States::setPause(true);
	}
}

void Engine::OnGameInactiveState()
{
	menu.Render(window, 10.0f, mainCamera.cameraView.getCenter());
}
