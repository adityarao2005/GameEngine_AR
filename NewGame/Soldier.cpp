#include "Soldier.h"

Soldier::Soldier(std::string image, sf::Vector2f location)
{
	Engine& engine = Engine::GetInstance();
	entity = engine.world->create();
	entity->assign<Sprite2D>(image);
	entity->assign<Tag>();
	entity->assign<FireDelay>();
	entity->get<FireDelay>()->delay = 500.0f;
	entity->assign<Transform>(location.x, location.y, 0.3f, 0.3f);
	entity->assign<std::vector<Bullet*>>(
		std::vector<Bullet*>());

	entity->assign<CallbackEntity>(Soldier::fire);
}

Soldier::~Soldier()
{
}

void Soldier::fire(ECS::Entity* entity) {
	ECS::ComponentHandle<Sprite2D> sprite = entity->get<Sprite2D>();
	ECS::ComponentHandle<Transform> transform = entity->get<Transform>();
	ECS::ComponentHandle<std::vector<Bullet*>> bullets = entity->get<std::vector<Bullet*>>();

	for (int i = bullets->size(); i >= 20; i--) {
		std::cout << "he" << std::endl;
		Bullet* bullet = bullets->at(0);
		bullets->erase(bullets->begin());
		delete bullet;
	}

	Bullet* bullet = new Bullet(sf::Vector2f(transform->xpos, transform->ypos), sprite->self.getRotation() - 90.0f, 0.1f);
	bullets->push_back(bullet);
}