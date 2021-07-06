#pragma once
class States
{
private:
	static bool pause;

public:
	static bool getPause();

	static void setPause(bool pause);
};

