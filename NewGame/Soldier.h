#pragma once
#include <GameEngine_AR\Engine.h>

class Soldier
{
protected:
	ECS::Entity* soldier;
	
public:
	Soldier(std::string image, sf::Vector2f location);
	~Soldier();

};

