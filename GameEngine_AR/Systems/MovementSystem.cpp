#define _USE_MATH_DEFINES
#include "MovementSystem.h"
#include <math.h>

MovementSystem::MovementSystem() : timer(0.0f) {}

MovementSystem::~MovementSystem() = default;

void MovementSystem::tick(ECS::World * world, float deltaTime)
{
	timer += deltaTime;
	if (!States::getPause())
	{
		world->each<Sprite2D, Tag, Transform>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<Sprite2D> sprite,
				ECS::ComponentHandle<Tag> tag,
				ECS::ComponentHandle<Transform> transform) -> void {
			sprite->self.setOrigin(sf::Vector2f(sprite->width / 2, sprite->height / 2));

			if (tag->containsTag("Player")) {
				ECS::ComponentHandle<InputController> input = entity->get<InputController>();
				if (input->inputActive) {
					if (input->down)
					{
						transform->xspeed = -sin((sprite->self.getRotation() + 90.0f) / 180.0f * M_PI) * transform->xspeedMod;
						transform->yspeed = cos((sprite->self.getRotation() + 90.0f) / 180.0f * M_PI) * transform->yspeedMod;

						transform->move();
					}
					else if (input->up)
					{
						transform->xspeed = sin((sprite->self.getRotation() + 90.0f) / 180.0f * M_PI) * transform->xspeedMod;
						transform->yspeed = -cos((sprite->self.getRotation() + 90.0f) / 180.0f * M_PI) * transform->yspeedMod;
						transform->move();
					}
					// DOWN (BACKWARD)
					else {
						transform->yspeed = 0;
						transform->xspeed = 0;
					}

					if (input->left) {
						sprite->self.rotate(-0.5f);
					}
					else if (input->right) {
						sprite->self.rotate(0.5f);
					}

					if (input->space) {
						ECS::ComponentHandle<FireDelay> delay = entity->get<FireDelay>();
						if (delay->timeSinceLastShot > delay->delay) {
							(entity->get<CallbackEntity>().get())(entity);
							delay->timeSinceLastShot = 0.0f;
						}
						else {
							delay->timeSinceLastShot += deltaTime;
						}
					}
				}
			}
			else if (tag->containsTag("Enemy")) {
				transform->xspeed = sin((sprite->self.getRotation() + 90.0f) / 180.0f * M_PI) * transform->xspeedMod / 2;
				transform->yspeed = -cos((sprite->self.getRotation() + 90.0f) / 180.0f * M_PI) * transform->yspeedMod / 2;
				transform->move();
				if (timer > 30000.0f) {
					int random = (rand() % 360) + 1;
					sprite->self.setRotation(random + 90.0f);
					
					timer = 0.0f;
				}
			}
			else if (tag->containsTag("Bullet")) {
				transform->xspeed = -sin(transform->rotation / 180.0f * M_PI) * transform->xspeedMod;
				transform->yspeed = cos(transform->rotation / 180.0f * M_PI) * transform->yspeedMod;

				transform->move();
			}
		});
	}
}
