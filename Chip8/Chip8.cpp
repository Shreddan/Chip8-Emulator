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

	for (int i = 0; i < 80; ++i)
	{
		mem[i] = chip8_fontset[i];
	}
}

void Chip8::emCycle()
{
    //Opcodes are two bytes
    opcode = mem[ProgCount] << 8 | mem[ProgCount + 1];

    //Decode Instructions
    switch (opcode & 0xFFFF)
    {
        case 0x00E0:
        {
            OP_00E0();
            break;
        }
        case 0x00EE:
        {
            OP_00EE();
            break;
        }
        case 0x1000:
        {
            OP_1NNN();
            break;
        }
        case 0x2000:
        {
            OP_2NNN();
            break;
        }
        case 0x3000:
        {
            OP_3XNN();
            break;
        }
    }
}

void Chip8::load()
{   
    OPENFILENAME ofn;
    wchar_t wcFile[MAX_PATH];
    char ncFile[MAX_PATH];
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = wcFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(wcFile);
    ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    GetOpenFileName(&ofn);

    wctomb(ncFile, *wcFile);

    std::ifstream fs(ncFile, std::ios::binary);

    fs.seekg(0, std::ios::end);
    size_t len = fs.tellg();
    char* temp = new char[len];
    fs.seekg(0, std::ios::beg);
    fs.read(temp, len);

    for (int i = 0; i < len; ++i)
    {
        mem[i + 512] = temp[i];
    }
}

void Chip8::OP_00E0()
{
    //Clears the Screen
    for (int i = 0; i < (64 * 32); i++)
    {
        gfx[i] = 0;
    }
}

void Chip8::OP_00EE()
{
    sp--;
    ProgCount = stack[sp];
}

void Chip8::OP_1NNN()
{
    uint16_t nnn = opcode & 0xFFF;
    ProgCount = nnn;
}

void Chip8::OP_2NNN()
{
    stack[sp] = ProgCount;
    ++sp;
    ProgCount = opcode & 0x0FFF;
}

void Chip8::OP_3XNN()
{
    uint8_t x = (opcode >> 8) & 0x000F;
    uint8_t nn = opcode & 0x00FF;
    if (V[x] == nn)
    {
        ProgCount += 2;
    }
}

void Chip8::OP_4XNN()
{
    uint8_t x = (opcode >> 8) & 0x000F;
    uint8_t nn = opcode & 0x00FF;
    if (V[x] != nn)
    {
        ProgCount += 2;
    }
}

void Chip8::OP_5XY0()
{
    uint8_t x = (opcode >> 8) & 0x000F;
    uint8_t y = (opcode >> 4) & 0x000F;
    if (V[x] == V[y])
    {
        ProgCount += 2;
    }
}

void Chip8::OP_6XNN()
{
    uint8_t x = (opcode >> 8) & 0x000F;
    uint8_t nn = opcode & 0x00FF;
    V[x] = nn;
}

void Chip8::OP_7XNN()
{
    uint8_t x = (opcode >> 8) & 0x000F;
    uint8_t nn = opcode & 0x00FF;
    V[x] = V[x] + nn;
}

void Chip8::OP_8XY0()
{
    uint8_t x = (opcode >> 8) & 0x000F;
    uint8_t y = (opcode >> 4) & 0x000F;
    V[x] = V[y];
}

void Chip8::OP_8XY1()
{
    uint8_t x = (opcode >> 8) & 0x000F;
    uint8_t y = (opcode >> 4) & 0x000F;
    V[x] = V[x] | V[y];
}

void Chip8::OP_8XY2()
{
    uint8_t x = (opcode >> 8) & 0x000F;
    uint8_t y = (opcode >> 4) & 0x000F;
    V[x] = V[x] & V[y];
}

void Chip8::OP_8XY3()
{
    uint8_t x = (opcode >> 8) & 0x000F;
    uint8_t y = (opcode >> 4) & 0x000F;
    V[x] = V[x] ^ V[y];
}

void Chip8::OP_8XY4()
{
    uint8_t x = (opcode >> 8) & 0x000F;
    uint8_t y = (opcode >> 4) & 0x000F;
    V[x] = V[x] + V[y];
    if (V[x] > 255)
    {
        V[0xF] = 1;
    }
    V[x] = V[x] & 0x00FF;
}

void Chip8::OP_8XY5()
{
    uint8_t x = (opcode >> 8) & 0x000F;
    uint8_t y = (opcode >> 4) & 0x000F;
    if (V[x] > V[y])
    {
        V[0xF] = 0;
    }
    V[x] = V[x] - V[y];
}

void Chip8::OP_8XY6()
{
    uint8_t y = (opcode >> 4) & 0x000F;
    uint8_t x = (opcode >> 8) & 0x000F;
    V[0xF] = V[y] & 0x0001;
    V[x] = V[y] >> 1;
}

void Chip8::OP_8XY7()
{
    uint8_t x = (opcode >> 8) & 0x000F;
    uint8_t y = (opcode >> 4) & 0x000F;
    V[x] = V[y] - V[x];
    if (V[x] > 255)
    {
        V[0xF] = 0;
    }
    else
    {
        V[0xF] = 1;
    }
}

void Chip8::OP_8XYE()
{

}