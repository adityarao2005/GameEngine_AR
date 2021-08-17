#pragma once
#include "..\Engine.h"

class TileMapSystem :
	public ECS::EntitySystem
{
public:
	TileMapSystem();

	~TileMapSystem();

	void tick(ECS::World* world, float deltaTime);

	void AddTileOnClick(bool hasCollision, ECS::ComponentHandle<TileMap> tilemap);
};

