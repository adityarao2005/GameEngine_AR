#include "States.h"

bool States::pause = false;

bool States::getPause()
{
	return pause;
}

void States::setPause(bool pause)
{
	States::pause = pause;
}
