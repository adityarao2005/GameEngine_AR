#pragma once
#include "Soldier.h"
class Enemy :
	public Soldier
{
public:
	Enemy(sf::Vector2f position);
	~Enemy();
};

