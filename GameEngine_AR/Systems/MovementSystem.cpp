#include "MovementSystem.h"

MovementSystem::MovementSystem() = default;

MovementSystem::~MovementSystem() = default;

void MovementSystem::tick(ECS::World * world, float deltaTime)
{
	if (!States::getPause())
	{
		world->each<InputController, Transform, Animator>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<InputController> input,
				ECS::ComponentHandle<Transform> transform,
				ECS::ComponentHandle<Animator> animator) -> void {
			if (input->inputActive == true) {
				// up
				if (input->w == true) {
					transform->yspeed = -transform->yspeedMod;
				}
				// down
				else if (input->s == true)
				{
					transform->yspeed = transform->yspeedMod;
				}
				// stop
				else {
					animator->currentRow = 0;
					transform->yspeed = 0.0f;
				}

				// left
				if (input->a == true) {
					transform->xspeed = -transform->xspeedMod;
					animator->facingRight = false;
					animator->currentRow = 1;
				}
				// right
				else if (input->d == true)
				{
					transform->xspeed = transform->xspeedMod;
					animator->facingRight = true;
				}
				// stop
				else {
					animator->currentColumn = 0;
					transform->xspeed = 0.0f;
				}
				transform->move();
			}
		});
	}
}
