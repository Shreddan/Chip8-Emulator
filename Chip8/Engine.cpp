#include "Engine.h"

Engine::Engine()
{
	sAppName = "Chip8 Emulator";
}

Engine::~Engine()
{
}

bool Engine::OnUserCreate()
{
	return true;
}

bool Engine::OnUserUpdate(float fElapsedTime)
{
	return true;
}
