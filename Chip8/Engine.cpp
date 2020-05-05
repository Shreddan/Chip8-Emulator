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
	mychip8.load();
	return true;
}

bool Engine::OnUserUpdate(float fElapsedTime)
{
	Clear(olc::BLACK);
	return true;
}
