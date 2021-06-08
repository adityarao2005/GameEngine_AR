#include "PhysicsSystem.h"

bool PhysicsSystem::isColliding(ECS::ComponentHandle<BoxCollider> touchingBox, ECS::ComponentHandle<BoxCollider> touchedBox, float x, float y)
{
	return
		touchingBox->rightEdge + x > touchedBox->leftEdge &&
		touchedBox->rightEdge > touchingBox->leftEdge + x &&
		touchingBox->bottomEdge + y > touchedBox->topEdge &&
		touchedBox->bottomEdge > touchingBox->topEdge + y;
}

bool PhysicsSystem::isColliding(ECS::ComponentHandle<BoxCollider> touchingBox, sf::RectangleShape touchedRectangle, float x, float y)
{
	float touchedRectLeft = touchedRectangle.getPosition().x;
	float touchedRectRight = touchedRectLeft + touchedRectangle.getGlobalBounds().width;
	float touchedRectTop = touchedRectangle.getPosition().y;
	float touchedRectBottom = touchedRectTop + touchedRectangle.getGlobalBounds().height;

	return
		touchingBox->rightEdge + x > touchedRectLeft &&
		touchedRectRight > touchingBox->leftEdge + x &&
		touchingBox->bottomEdge + y > touchedRectTop &&
		touchedRectBottom > touchingBox->topEdge + y;
}

bool PhysicsSystem::isColliding(ECS::ComponentHandle<BoxCollider> touchingBox, sf::RectangleShape touchedRectangle)
{
	float touchedRectLeft = touchedRectangle.getPosition().x;
	float touchedRectRight = touchedRectLeft + touchedRectangle.getGlobalBounds().width;
	float touchedRectTop = touchedRectangle.getPosition().y;
	float touchedRectBottom = touchedRectTop + touchedRectangle.getGlobalBounds().height;

	return
		touchingBox->rightEdge > touchedRectLeft &&
		touchedRectRight > touchingBox->leftEdge &&
		touchingBox->bottomEdge > touchedRectTop &&
		touchedRectBottom > touchingBox->topEdge;
}

bool PhysicsSystem::isColliding(ECS::ComponentHandle<BoxCollider> touchingBox, ECS::ComponentHandle<BoxCollider> touchedBox) {
	return
		touchingBox->rightEdge > touchedBox->leftEdge &&
		touchedBox->rightEdge > touchingBox->leftEdge &&
		touchingBox->bottomEdge > touchedBox->topEdge &&
		touchedBox->bottomEdge > touchingBox->topEdge;
}

void PhysicsSystem::checkCollisionSides(ECS::ComponentHandle<Transform> transform, ECS::ComponentHandle<BoxCollider> touchingBox, ECS::ComponentHandle<BoxCollider> touchedBox)
{
	// Scenerio dealing with collision from the right side by accelerating right ward
	if (transform->xspeed > 0 &&
		touchedBox->rightEdge + transform->xspeed > touchedBox->leftEdge &&
		touchingBox->topEdge < touchedBox->bottomEdge &&
		touchingBox->bottomEdge > touchedBox->topEdge) {
		transform->xspeed = 0;
	}

	// Scenerio dealing with collision from the bottom side by accelerating down ward
	if (transform->yspeed > 0 &&
		touchedBox->bottomEdge + transform->yspeed > touchedBox->topEdge &&
		touchingBox->leftEdge < touchedBox->rightEdge &&
		touchingBox->rightEdge > touchedBox->leftEdge) {
		transform->yspeed = 0;
	}

	// Scenerio dealing with collision from the right side by accelerating right ward
	if (transform->xspeed < 0 &&
		touchedBox->leftEdge + transform->xspeed > touchedBox->rightEdge &&
		touchingBox->topEdge < touchedBox->bottomEdge &&
		touchingBox->bottomEdge > touchedBox->topEdge) {
		transform->xspeed = 0;
	}

	// Scenerio dealing with collision from the top side by accelerating down ward
	if (transform->yspeed < 0 &&
		touchedBox->topEdge + transform->yspeed > touchedBox->bottomEdge &&
		touchingBox->leftEdge < touchedBox->rightEdge &&
		touchingBox->rightEdge > touchedBox->leftEdge) {
		transform->yspeed = 0;
	}
}

void PhysicsSystem::checkCollisionSides(ECS::ComponentHandle<Transform> transform, ECS::ComponentHandle<BoxCollider> touchingBox, sf::RectangleShape touchedRectangle)
{
	float touchedRectLeft = touchedRectangle.getPosition().x;
	float touchedRectRight = touchedRectLeft + touchedRectangle.getGlobalBounds().width;
	float touchedRectTop = touchedRectangle.getPosition().y;
	float touchedRectBottom = touchedRectTop + touchedRectangle.getGlobalBounds().height;

	// Scenerio dealing with collision from the right side by accelerating right ward
	if (transform->xspeed > 0 &&
		touchedRectRight + transform->xspeed > touchedRectLeft &&
		touchingBox->topEdge < touchedRectBottom &&
		touchingBox->bottomEdge > touchedRectTop) {
		transform->xspeed = 0;
	}

	// Scenerio dealing with collision from the bottom side by accelerating down ward
	if (transform->yspeed > 0 &&
		touchedRectBottom + transform->yspeed > touchedRectTop &&
		touchingBox->leftEdge < touchedRectRight &&
		touchingBox->rightEdge > touchedRectLeft) {
		transform->yspeed = 0;
	}

	// Scenerio dealing with collision from the right side by accelerating right ward
	if (transform->xspeed < 0 &&
		touchedRectLeft + transform->xspeed > touchedRectRight &&
		touchingBox->topEdge < touchedRectBottom &&
		touchingBox->bottomEdge > touchedRectTop) {
		transform->xspeed = 0;
	}

	// Scenerio dealing with collision from the top side by accelerating down ward
	if (transform->yspeed < 0 &&
		touchedRectTop + transform->yspeed > touchedRectBottom &&
		touchingBox->leftEdge < touchedRectRight &&
		touchingBox->rightEdge > touchedRectLeft) {
		transform->yspeed = 0;
	}
}

void PhysicsSystem::checkCollisionSides(ECS::Entity * touchingEntity, ECS::Entity * touchedEntity)
{
	float newTouchingX = touchingEntity->get<Transform>()->xpos;
	float newTouchingY = touchingEntity->get<Transform>()->ypos;
	float newTouchingXspeed = touchingEntity->get<Transform>()->xspeed;
	float newTouchingYspeed = touchingEntity->get<Transform>()->yspeed;

	float newTouchedX = touchedEntity->get<Transform>()->xpos;
	float newTouchedY = touchedEntity->get<Transform>()->ypos;
	float newTouchedXspeed = touchedEntity->get<Transform>()->xspeed;
	float newTouchedYspeed = touchedEntity->get<Transform>()->yspeed;

	if (newTouchingXspeed > 0 && newTouchingX < newTouchedX) {
		touchedEntity->get<Transform>()->xpos++;
	}
	else if (newTouchingXspeed < 0 && newTouchingX > newTouchedX) {
		touchedEntity->get<Transform>()->xpos--;
	}
	if (newTouchingYspeed > 0 && newTouchingY < newTouchedY) {
		touchedEntity->get<Transform>()->ypos++;
	}
	else if (newTouchingYspeed < 0 && newTouchingY > newTouchedY) {
		touchedEntity->get<Transform>()->ypos--;
	}
}

void PhysicsSystem::tick(ECS::World * world, float deltaTime)
{
	world->each<BoxCollider, Sprite2D, Transform>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<BoxCollider> collider,
			ECS::ComponentHandle<Sprite2D> sprite,
			ECS::ComponentHandle<Transform> transform) -> void {
		collider->update(
			transform->xpos,
			transform->ypos,
			sprite->self.getTextureRect().width,
			sprite->self.getTextureRect().height);
	});

	// collider for box and transform entities
	world->each<BoxCollider, Transform>(
		[&](ECS::Entity* touchingEntity,
			ECS::ComponentHandle<BoxCollider> touchingBox,
			ECS::ComponentHandle<Transform> transform) -> void {
		world->each<BoxCollider>(
			[&](ECS::Entity* touchedEntity,
				ECS::ComponentHandle<BoxCollider> touchedBox) -> void {
			// Statement to avoid comparing the same entity to itself
			// initial collision check
			if (touchingEntity->getEntityId() == touchedEntity->getEntityId() || !isColliding(touchingBox, touchedBox)) {
				return;
			}

			// final collision check
			checkCollisionSides(touchingEntity, touchedEntity);
		});
	});

	// actual push
	world->each<Transform>(
		[&](ECS::Entity* entity, ECS::ComponentHandle<Transform> transform) -> void {
		transform->move();
	});
}
