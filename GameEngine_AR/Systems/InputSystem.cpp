#include "InputSystem.h"

InputSystem::InputSystem(sf::RenderWindow * window)
{
	this->window = window;
}

InputSystem::~InputSystem() = default;

void InputSystem::tick(ECS::World * world, float deltaTime)
{
	getKeyEvents(world);
}

void InputSystem::getKeyEvents(ECS::World * world)
{
	if (!States::getPause())
	{
		world->each<struct InputController>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<struct InputController> input) -> void {
			input->w = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
			input->a = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
			input->s = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
			input->d = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
			input->left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
			input->right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
			input->up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
			input->down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
		});
	}
}
