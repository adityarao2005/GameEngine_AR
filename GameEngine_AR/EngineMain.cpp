#include <SFML\Graphics.hpp>
#include "Engine.h"

int main(int argc, char* args[]) {
	// Declare and get instance of singleton
	Engine& engine = Engine::GetInstance();

	sf::RenderWindow window(sf::VideoMode(800, 600), "Game Engine");

	// Pass window reference of window and Start
	engine.Start(&window);

	return 0;
}