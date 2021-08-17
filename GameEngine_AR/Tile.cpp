#include "Tile.h"

Tile::Tile() = default;

Tile::Tile(float xpos, float ypos, float gridSize, bool colliding)
{
	shape.setSize(sf::Vector2f(gridSize, gridSize));
	shape.setFillColor(sf::Color::Black);
	shape.setPosition(sf::Vector2f(xpos * gridSize, ypos * gridSize));
	this->colliding = colliding;
}

Tile::~Tile() = default;

void Tile::Render(sf::RenderTarget & target)
{
	target.draw(shape);
}

const bool & Tile::GetCollision() const
{
	return colliding;
}

const sf::Vector2f & Tile::GetPosition() const
{
	return shape.getPosition();
}

std::string Tile::ToString()
{
	std::stringstream stringform;
	stringform << colliding << " ";
	return stringform.str();
}
