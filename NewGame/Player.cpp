#include "Player.h"

Player::Player(sf::Vector2f position) : Soldier("../Debug/Pics/Player_1.png", position)
{
	soldier->assign<InputController>();
	soldier->get<Tag>()->addTag("Player");
}

Player::~Player() = default;
