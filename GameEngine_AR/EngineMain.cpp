#include <SFML\Graphics.hpp>

int main(int argc, char* args[]) {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Game Engine");

	// run the program as long as the window is open
	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			// close reqquested event

			if (event.type == sf::Event::Closed) {
				window.close();
				break;
			}
		}
	}

	return 0;
}