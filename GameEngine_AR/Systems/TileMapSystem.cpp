#include "TileMapSystem.h"

TileMapSystem::TileMapSystem() = default;

TileMapSystem::~TileMapSystem() = default;

void TileMapSystem::tick(ECS::World * world, float deltaTime)
{
	if (!States::getPause()) {
		Engine::GetInstance().world->each<TileMap>(
		[&](ECS::Entity* entity, ECS::ComponentHandle<TileMap> tilemap) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				AddTileOnClick(true, tilemap);
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				AddTileOnClick(false, tilemap);
			}

			if (ButtonMap::getMap()["SAVE"]->clicked) {
				std::cout << "Save" << std::endl;
				tilemap->SaveTileMap("TileText.txt");
				ButtonMap::getMap()["SAVE"]->clicked = false;
			}

			if (ButtonMap::getMap()["LOAD"]->clicked) {
				std::cout << "Save" << std::endl;
				tilemap->LoadTileMap("TileText.txt");
				ButtonMap::getMap()["LOAD"]->clicked = false;
			}
		});
	}
}

void TileMapSystem::AddTileOnClick(bool hasCollision, ECS::ComponentHandle<TileMap> tilemap)
{
	sf::RenderWindow* ref = Engine::GetInstance().window;
	sf::Vector2f mousePos = ref->mapPixelToCoords(sf::Mouse::getPosition(*ref));
	sf::Vector2i mousePosGrid(static_cast<int>(mousePos.x/ tilemap->gridSizeF), static_cast<int>(mousePos.y / tilemap->gridSizeF));
	tilemap->AddTile(mousePosGrid.x, mousePosGrid.y, 0, hasCollision);

}
