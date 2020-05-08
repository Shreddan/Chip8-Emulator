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
	mychip8.emCycle();

	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			if (mychip8.gfx[i] == 1)
			{
				Draw(i, j);
			}
		}
	}
	return true;
}
