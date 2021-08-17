#include "MainCamera.h"

MainCamera::MainCamera() = default;

MainCamera::MainCamera(sf::Vector2f pivot)
{
	cameraView.setCenter(pivot);
}

MainCamera::~MainCamera() = default;

void MainCamera::Update(ECS::World * world, float deltaTime, sf::RenderWindow * gameWindow)
{
	cameraView.setSize(gameWindow->getSize().x, gameWindow->getSize().y);
	float cameraMoveSpeed = 0.1f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		cameraView.move(-cameraMoveSpeed * deltaTime, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		cameraView.move(cameraMoveSpeed * deltaTime, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		cameraView.move(0, -cameraMoveSpeed * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		cameraView.move(0, cameraMoveSpeed * deltaTime);
	}

	gameWindow->setView(cameraView);
}
