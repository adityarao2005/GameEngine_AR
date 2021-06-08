#pragma once
#include "..\Engine.h"

class InputSystem : public ECS::EntitySystem
{
private:
	sf::RenderWindow* window;

public:
	InputSystem() = default;

	InputSystem(sf::RenderWindow* window);

	~InputSystem();

	void tick(ECS::World* world, float deltaTime) override;

	void getKeyEvents(ECS::World* world);
};

