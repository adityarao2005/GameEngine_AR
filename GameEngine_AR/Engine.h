#pragma once
#include <SFML\Graphics.hpp>

class Engine
{
public:
	sf::RenderWindow* window;

	// start the window
	void Start(sf::RenderWindow* window);

	// Singleton - instantiate only once 
	static Engine& GetInstance();
private:
	bool quit;

	Engine();

	// Required to prevent the reference from being copied, moved, or assigned
	Engine(Engine& copy); // hide copy constructor

	Engine(Engine&& move); // hide move constructor

	Engine& operator =(Engine& copy); // hide assignment operator

	~Engine();

	void Update();
};

