#pragma once
#include <GameEngine_AR\Engine.h>
#include "Entity.h"
#include "Bullet.h"
#include <list>

class Soldier : public Entity
{
private:
	int delay;

	static void fire(ECS::Entity* entity);
public:

	Soldier(std::string image, sf::Vector2f location);
	~Soldier();

};

