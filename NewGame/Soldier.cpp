#include "Soldier.h"

Soldier::Soldier(std::string image, sf::Vector2f location)
{
	Engine& engine = Engine::GetInstance();
	soldier = engine.world->create();
	soldier->assign<Sprite2D>(image);
	soldier->assign<Tag>();
	soldier->assign<Transform>(location.x, location.y, 0.3f, 0.3f);
}

Soldier::~Soldier()
{
}
