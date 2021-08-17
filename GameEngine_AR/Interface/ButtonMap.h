#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

class ButtonMap
{
public:
	static std::map<std::string, Button*>& getMap();
};

