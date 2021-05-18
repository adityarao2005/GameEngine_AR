#include <SFML\Graphics.hpp>
#include "Engine.h"
#include <iostream>

int main(int argc, char* args[]) {
	// Declare and get instance of singleton
	Engine& engine = Engine::GetInstance();

	sf::RenderWindow window(sf::VideoMode(800, 600), "Game Engine");

	// Create the world for attaching entity and systems to
	engine.world = ECS::World::createWorld();
	
	// Define entities here
	ECS::Entity* background;
	ECS::Entity* tux;
	ECS::Entity* stickFigure;

	// Add Systems to the engine
	engine.AddSystem(new RenderingSystem());
	engine.AddSystem(new AnimationSystem());

	// Creating the entities
	background = engine.world->create();
	tux = engine.world->create();
	stickFigure = engine.world->create();

	// Assign components after entity creation
	background->assign<Transform>(0, 0);
	background->assign<Sprite2D>("../Debug/Pics/bg.jpg");

	tux->assign<Transform>(200, 200);
	tux->assign<Sprite2D>("../Debug/Pics/tux_from_linux.png");
	tux->assign<Animator>(56, 72, 2000.0f, 3, 9);

	stickFigure->assign<Transform>(300, 300);
	stickFigure->assign<Sprite2D>("../Debug/Pics/herosheet.png");
	stickFigure->assign<Animator>(32, 32, 200.0f, 4, 1);
	
	std::cout << background->getEntityId() << " is the entity ID" << std::endl;
	std::cout << tux->getEntityId() << " is the entity ID" << std::endl;
	std::cout << stickFigure->getEntityId() << " is the entity ID" << std::endl;

	
	// Pass window reference of window and Start
	engine.Start(&window);

	return 0;
}
