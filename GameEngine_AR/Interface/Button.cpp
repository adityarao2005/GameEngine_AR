#include "Button.h"

Button::Button() = default;

Button::Button(sf::Vector2f size, sf::Color color, std::string text) : 
	defaultColor(color), highlightedColor(defaultColor.r + 50, defaultColor.g + 50, defaultColor.b + 50)
{
	buttonBG.setSize(size);
	buttonBG.setFillColor(defaultColor);
	buttonBG.setPosition(0, 0);
	buttonText.setCharacterSize(11);
	buttonText.setFillColor(sf::Color::White);
	buttonText.setPosition(0, 0);
	buttonText.setString(text);
}

Button::~Button() = default;

bool Button::isHighlighted()
{
	return highlighted;
}

void Button::highlight(sf::RenderWindow * window)
{
	highlighted = buttonBG.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
	if (highlighted) {
		buttonBG.setFillColor(highlightedColor);
	}
	else {
		buttonBG.setFillColor(defaultColor);
	}
}

void Button::update(sf::Event event, float deltaTime)
{
	checkPressed(event);
}

void Button::render(sf::RenderWindow * window, float deltaTime)
{
	window->draw(buttonBG);
	window->draw(buttonText);
	window->display();
}

void Button::checkPressed(sf::Event event)
{
	if (!highlighted) {
		return;
	}


	if (event.type == sf::Event::MouseButtonPressed) {
		pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

		if (!pressed) {
			clicked = false;
		}
	}

	if (pressed) {
		if (event.type == sf::Event::MouseButtonReleased) {
			released = true;
			clicked = true;
		}
	}
	else {
		released = false;
		clicked = false;
	}
}
