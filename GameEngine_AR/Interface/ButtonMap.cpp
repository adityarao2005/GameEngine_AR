#include "ButtonMap.h"

std::map<std::string, Button*>& ButtonMap::getMap() {
	static std::map<std::string, Button*> map;
	return map;
}