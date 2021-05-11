#include "AnimationSystem.h"

AnimationSystem::AnimationSystem() = default;

AnimationSystem::~AnimationSystem() = default;

void AnimationSystem::tick(ECS::World * world, float deltaTime)
{
	world->each<struct Animator, struct Sprite2D>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<Animator> animator,
			ECS::ComponentHandle<Sprite2D> sprite) -> void 
		{
			sprite->self.setTextureRect(
				sf::IntRect(
					animator->currentColumn * animator->spriteWidth, // Left / right sides
					animator->currentRow * animator->spriteHeight, // Top / Bottom sides
					animator->spriteWidth,
					animator->spriteHeight
				)
			); 
		});

}
