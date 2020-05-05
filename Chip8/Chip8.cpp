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
    opcode = mem[ProgCount] << 8 | mem[ProgCount + 1];


    switch (opcode & 0xF000)
    {
        
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
