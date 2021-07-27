#include "PauseMenu.h"

PauseMenu::PauseMenu() = default;

PauseMenu::PauseMenu(sf::RenderWindow * window)
{
	States::setPause(false);
	InitButtons();
}

PauseMenu::~PauseMenu() = default;

void PauseMenu::Update(sf::Event event, float deltaTime, sf::RenderWindow * window)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			States::setPause(!States::getPause());
	}

	if (States::getPause()) {
		ButtonMap::getMap()["RESUME"]->update(event, deltaTime);
		ButtonMap::getMap()["SAVE"]->update(event, deltaTime);
		ButtonMap::getMap()["QUIT"]->update(event, deltaTime);
		ButtonMap::getMap()["LOAD"]->update(event, deltaTime);

		if (ButtonMap::getMap()["RESUME"]->clicked) {
			// do stuff
			States::setPause(false);
			ButtonMap::getMap()["RESUME"]->clicked = false;
		}

		if (ButtonMap::getMap()["QUIT"]->clicked) {
			Quit(window);
			ButtonMap::getMap()["RESUME"]->clicked = false;
		}
	}
}

void PauseMenu::Render(sf::RenderWindow* window, float deltaTime, sf::Vector2f resumePosition)
{
	// Terminal
	sf::Font font;
	font.loadFromFile("../Debug/Fonts/impact.ttf");
	sf::Vector2f sizeOffset = ButtonMap::getMap()["RESUME"]->buttonBG.getSize() / 2.0f;

	ButtonMap::getMap()["RESUME"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, -80) - sizeOffset);
	ButtonMap::getMap()["RESUME"]->buttonText.setFont(font);
	ButtonMap::getMap()["RESUME"]->buttonText.setPosition(ButtonMap::getMap()["RESUME"]->buttonBG.getPosition());
	ButtonMap::getMap()["RESUME"]->highlight(window);
	ButtonMap::getMap()["RESUME"]->render(window, deltaTime);

	ButtonMap::getMap()["LOAD"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, -40) - sizeOffset);
	ButtonMap::getMap()["LOAD"]->buttonText.setFont(font);
	ButtonMap::getMap()["LOAD"]->buttonText.setPosition(ButtonMap::getMap()["LOAD"]->buttonBG.getPosition());
	ButtonMap::getMap()["LOAD"]->highlight(window);
	ButtonMap::getMap()["LOAD"]->render(window, deltaTime);

	ButtonMap::getMap()["SAVE"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, 0) - sizeOffset);
	ButtonMap::getMap()["SAVE"]->buttonText.setFont(font);
	ButtonMap::getMap()["SAVE"]->buttonText.setPosition(ButtonMap::getMap()["SAVE"]->buttonBG.getPosition());
	ButtonMap::getMap()["SAVE"]->highlight(window);
	ButtonMap::getMap()["SAVE"]->render(window, deltaTime);

	ButtonMap::getMap()["QUIT"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, 40) - sizeOffset);
	ButtonMap::getMap()["QUIT"]->buttonText.setFont(font);
	ButtonMap::getMap()["QUIT"]->buttonText.setPosition(ButtonMap::getMap()["QUIT"]->buttonBG.getPosition());
	ButtonMap::getMap()["QUIT"]->highlight(window);
	ButtonMap::getMap()["QUIT"]->render(window, deltaTime);

	window->display();
}

void PauseMenu::InitButtons()
{
	sf::Vector2f size(125, 35);
	ButtonMap::getMap().insert(
		{
		"RESUME", new Button(size, sf::Color(100, 100, 100, 255), "RESUME GAME")
		});
	ButtonMap::getMap().insert(
		{
		"LOAD", new Button(size, sf::Color(100, 100, 100, 255), "LOAD TILEMAP")
		});
	ButtonMap::getMap().insert(
		{
		"SAVE", new Button(size, sf::Color(100, 100, 100, 255), "SAVE TILEMAP")
		});
	ButtonMap::getMap().insert(
		{
		"QUIT", new Button(size, sf::Color(100, 100, 100, 255), "QUIT GAME")
		});
}

void PauseMenu::Quit(sf::RenderWindow * window)
{
	window->close();
}
