#define _USE_MATH_DEFINES
#include "MovementSystem.h"
#include <math.h>

MovementSystem::MovementSystem() = default;

MovementSystem::~MovementSystem() = default;

void MovementSystem::tick(ECS::World * world, float deltaTime)
{
	if (!States::getPause())
	{
		world->each<Sprite2D, Tag, Transform>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<Sprite2D> sprite,
				ECS::ComponentHandle<Tag> tag,
				ECS::ComponentHandle<Transform> transform) -> void {
			sprite->self.setOrigin(sf::Vector2f(sprite->width / 2, sprite->height / 2));

			if (std::find(tag->tagnames.begin(), tag->tagnames.end(), "Player") != tag->tagnames.end()) {

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
				}
			}
			else if (std::find(tag->tagnames.begin(), tag->tagnames.end(), "Enemy") != tag->tagnames.end()) {
				
			}
		});
	}
}
