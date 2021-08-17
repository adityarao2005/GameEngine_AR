#pragma once
#include "..\Engine.h"

class PhysicsSystem : public ECS::EntitySystem
{
public:
	PhysicsSystem() = default;

	~PhysicsSystem() = default;

	bool isColliding(
		ECS::ComponentHandle<BoxCollider> touchingBox,
		ECS::ComponentHandle<BoxCollider> touchedBox,
		float x, float y
	);

	bool isColliding(
		ECS::ComponentHandle<BoxCollider> touchingBox,
		sf::RectangleShape touchedRectangle,
		float x, float y
	);

	bool isColliding(
		ECS::ComponentHandle<BoxCollider> touchingBox,
		sf::RectangleShape touchedBox
	);

	bool isColliding(
		ECS::ComponentHandle<BoxCollider> touchingBox,
		ECS::ComponentHandle<BoxCollider> touchedBox
	);

	void checkCollisionSides(
		ECS::ComponentHandle<Transform> transform,
		ECS::ComponentHandle<BoxCollider> touchingBox,
		ECS::ComponentHandle<BoxCollider> touchedBox
	);

	void checkCollisionSides(
		ECS::ComponentHandle<Transform> transform,
		ECS::ComponentHandle<BoxCollider> touchingBox,
		sf::RectangleShape touchedRectangle
	);

	void checkCollisionSides(
		ECS::Entity* touchingEntity,
		ECS::Entity* touchedEntity
	);

	void tick(ECS::World* world, float deltaTime) override;
};

