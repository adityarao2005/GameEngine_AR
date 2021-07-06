#pragma once
#include <SFML\Graphics.hpp>
#include "ECS.h"
#include "Components.h"
#include "Systems\RenderingSystem.h"
#include "Systems\AnimationSystem.h"
#include "Systems\InputSystem.h"
#include "Systems\MovementSystem.h"
#include "Systems\PhysicsSystem.h"
#include "Interface\MainCamera.h"
#include "Interface\PauseMenu.h"

class Engine
{
public:
	sf::RenderWindow* window;
	ECS::World* world;
	MainCamera mainCamera;
	PauseMenu menu;

	// start the window
	void Start(sf::RenderWindow* window);

	void AddSystem(ECS::EntitySystem* system);

	// Singleton - instantiate only once 
	static Engine& GetInstance();

	
private:
	bool quit;

	Engine();

	// Required to prevent the reference from being copied, moved, or assigned
	Engine(Engine& copy); // hide copy constructor

	Engine(Engine&& move); // hide move constructor

	Engine& operator =(Engine& copy) = default; // hide assignment operator

	~Engine();

	void Update();

	void OnGameInactiveState();
};

