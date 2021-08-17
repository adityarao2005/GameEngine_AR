#pragma once
#include "..\Engine.h"

class Soldier;
class MovementSystem : public ECS::EntitySystem
{
	float timer = 0;
public:
	MovementSystem();

	~MovementSystem();

	void tick(ECS::World* world, float deltaTime) override;
};

