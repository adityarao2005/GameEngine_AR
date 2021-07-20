#pragma once
#include <sstream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Tile
{
public:
	bool colliding;
	sf::RectangleShape shape;

	Tile();

	Tile(float xpos, float ypos, float gridSize, bool colliding);

	~Tile();

	void Render(sf::RenderTarget& target);

	const bool& GetCollision() const;

	const sf::Vector2f& GetPosition() const;

	std::string ToString();
};

