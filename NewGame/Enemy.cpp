#include "Enemy.h"

Enemy::Enemy(sf::Vector2f position) : Soldier("../Debug/Pics/Enemy_1.png", position)
{
	soldier->get<Tag>()->addTag("Enemy");
}

Enemy::~Enemy() = default;
