#pragma once
#include <olcPixelGameEngine.h>
#include "Chip8.h"

class Engine : public olc::PixelGameEngine
{
public:
	Engine();
	~Engine();

	bool OnUserCreate();
	bool OnUserUpdate(float fElapsedTime);

	Chip8 mychip8;
};

