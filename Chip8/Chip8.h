#pragma once
class Chip8
{
public:
	Chip8();
	~Chip8();

	unsigned short opcode;
	unsigned char mem[4096];
	unsigned char V[16];
	unsigned short IndexReg;
	unsigned short ProgCount;
	unsigned char gfx[64 * 32];
	unsigned char delayTimer;
	unsigned char soundTimer;

	unsigned short stack[16];
	unsigned short sp;

	unsigned char key[16];

	void initialise();

	void emCycle();
};

