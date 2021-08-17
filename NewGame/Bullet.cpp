#include "Bullet.h"

Bullet::Bullet(sf::Vector2f location, float angle, float speed)
{
	Engine& engine = Engine::GetInstance();
	entity = engine.world->create();
	entity->assign<Sprite2D>("../Debug/Pics/Bullet_1.png");
	entity->assign<Tag>();
	entity->get<Tag>()->addTag("Bullet");
	entity->assign<Transform>(location.x, location.y, speed, speed, angle);
}

Bullet::~Bullet()
{
	Engine& engine = Engine::GetInstance();
	engine.world->destroy(entity);
}
