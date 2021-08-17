#pragma once
#include "Entity.h"

class Bullet : public Entity
{
private:
	float delay;
public:
	Bullet(sf::Vector2f location, float angle, float speed);
	~Bullet();
};

