#include "Chip8.h"

Chip8::Chip8()
{
	initialise();
}

Chip8::~Chip8()
{
}

void Chip8::initialise()
{
	opcode = 0;
	ProgCount = 0x200;
	IndexReg = 0;
	sp = 0;
}

void Chip8::emCycle()
{
}
