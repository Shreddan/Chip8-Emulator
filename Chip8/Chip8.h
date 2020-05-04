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
};

