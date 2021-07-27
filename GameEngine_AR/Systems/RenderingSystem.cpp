#include "RenderingSystem.h"
#include <iostream>

sf::Texture* RenderingSystem::loadTexture(std::string filepath)
{
	sf::Texture* texture = new sf::Texture();

	if (!texture->loadFromFile(filepath)) {
		std::cerr << "Error:-----------------------------------" << std::endl;
		std::cerr << "Unable to load image: " << filepath << std::endl << "Is this image the current directory" << std::endl;
		system("pause");
		exit(EXIT_FAILURE);
	}

	return texture;
}

RenderingSystem::RenderingSystem() = default;

RenderingSystem::~RenderingSystem() = default;

void RenderingSystem::tick(ECS::World* world, float deltaTime)
{
	if (!States::getPause())
	{
		// Clear before drawing all textures
		Engine::GetInstance().window->clear();

		world->each<struct Transform, struct Sprite2D>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<Transform> transform,
				ECS::ComponentHandle<Sprite2D> sprite
				) -> void
		{
			// Check if an entity has their filePath loaded
			if (textureMap.count(sprite->texture) < 1)
			{
				textureMap[sprite->texture] = loadTexture(sprite->texture);
			}

			// If no filePath is found, add it
			if (sprite->self.getTexture() == nullptr)
			{
				sprite->self.setTexture(*textureMap[sprite->texture]);
				sprite->width = (int)std::floor(sprite->self.getGlobalBounds().width);
				sprite->height = (int)std::floor(sprite->self.getGlobalBounds().height);
			}

			// Update and draw to the screen
			sprite->self.setPosition(transform->xpos, transform->ypos);
			Engine::GetInstance().window->draw(sprite->self);
		});

		world->each<struct TileMap>(
			[&](ECS::Entity* ent,
				ECS::ComponentHandle<struct TileMap> tileMap) -> void
		{
			// Loop through each tile and render onto the engine's window instance
			// note that this is looping through a vector which stores a vector, which stores the tile value
			for (auto& x : tileMap->map)
			{
				for (auto& y : x)
				{
					for (auto& z : y)
					{
						if (z == nullptr)
						{
							continue;
						}

						sf::RenderWindow* _winRef = Engine::GetInstance().window;

						_winRef->draw(z->shape);

						if (z->GetCollision() == true)
						{
							tileMap->collisionBox.setPosition(z->GetPosition());
							_winRef->draw(tileMap->collisionBox);
						}

						//std::cout << "Placed" << std::endl;
					}
				}
			}
		});

		// Display updates
		Engine::GetInstance().window->display();
	}
}
