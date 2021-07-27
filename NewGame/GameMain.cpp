#include <SFML\Graphics.hpp>
#include <GameEngine_AR\Engine.h>
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
	ECS::Entity* gun;

	// Add Systems to the engine
	engine.AddSystem(new RenderingSystem());
	engine.AddSystem(new AnimationSystem());
	engine.AddSystem(new InputSystem(&window));
	engine.AddSystem(new MovementSystem());
	engine.AddSystem(new PhysicsSystem());
	engine.AddSystem(new TileMapSystem());

	// Creating the entities
	background = engine.world->create();
	tux = engine.world->create();
	stickFigure = engine.world->create();
	gun = engine.world->create();

	// Assign components after entity creation
	background->assign<Transform>(0, 0);
	background->assign<Sprite2D>("../Debug/Pics/bg.jpg");
	background->assign<TileMap>();

	tux->assign<Transform>(200, 200, 0.3f, 0.3f);
	tux->assign<Sprite2D>("../Debug/Pics/tux_from_linux.png");
	tux->assign<Animator>(56, 72, 2000.0f, 3, 9);
	tux->assign<InputController>();
	tux->assign<BoxCollider>();
	tux->assign<Tag>();
	tux->assign<MainCamera>(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	tux->get<Tag>()->addTag("Player");

	stickFigure->assign<Transform>(300, 300);
	stickFigure->assign<Sprite2D>("../Debug/Pics/herosheet.png");
	stickFigure->assign<Animator>(32, 32, 200.0f, 4, 1);
	stickFigure->assign<BoxCollider>();

	gun->assign<Transform>(300, 300);
	gun->assign<Sprite2D>("../Debug/Pics/pistol.png");
	gun->assign<BoxCollider>();
	gun->assign<Tag>();
	gun->get<Tag>()->addTag("Object");

	std::cout << background->getEntityId() << " is the entity ID" << std::endl;
	std::cout << tux->getEntityId() << " is the entity ID" << std::endl;
	std::cout << stickFigure->getEntityId() << " is the entity ID" << std::endl;


	// Pass window reference of window and Start
	engine.Start(&window);

	return 0;
}
