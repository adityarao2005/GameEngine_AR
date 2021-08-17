#pragma once
#include <SFML\Graphics.hpp>

class Button
{
private:
	sf::Color defaultColor, highlightedColor;

public:
	sf::RectangleShape buttonBG;
	sf::Text buttonText;
	bool pressed = false, clicked = false, released = false, highlighted = false;

	Button();

	Button(sf::Vector2f size, sf::Color color, std::string text);

	~Button();

	bool isHighlighted();

	void highlight(sf::RenderWindow* window);

	void update(sf::Event event, float deltaTime);

	void render(sf::RenderWindow* window, float deltaTime);

	void checkPressed(sf::Event event);
};

