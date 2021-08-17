#pragma once
#include "..\Engine.h"

class RenderingSystem : public ECS::EntitySystem
{
private:
	std::unordered_map<std::string, sf::Texture*> textureMap;

	sf::Texture* loadTexture(std::string texture);

public:
	RenderingSystem();

	~RenderingSystem();

	void tick(ECS::World* world, float deltaTime) override;

};

