#include <SFML\Graphics.hpp>
#include <GameEngine_AR\Engine.h>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

int main(int argc, char* args[]) {
	// Declare and get instance of singleton
	Engine& engine = Engine::GetInstance();

	sf::RenderWindow window(sf::VideoMode(800, 600), "Game Engine");

	// Create the world for attaching entity and systems to
	engine.world = ECS::World::createWorld();

	// Add Systems to the engine
	engine.AddSystem(new InputSystem());
	engine.AddSystem(new RenderingSystem());
	engine.AddSystem(new MovementSystem());

	Player player = Player(sf::Vector2f(300, 300));
	Enemy enemy = Enemy(sf::Vector2f(220, 200));
	//Bullet bullet = Bullet(sf::Vector2f(300, 300), -90.0f, 0.5f);
	
	// Pass window reference of window and Start
	engine.Start(&window);

	return 0;
}
