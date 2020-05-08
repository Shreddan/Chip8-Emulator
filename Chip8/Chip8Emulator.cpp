#define OLC_PGE_APPLICATION
#include <iostream>
#include "Engine.h"

int main()
{
    const int width = 400;
    const int height = width * 9 / 16;
    Engine engine;
    if (!engine.Construct(width, height, 2, 2)) 
    { 
        return 1; 
    }
    else 
    {
        engine.Start();
    }
}
