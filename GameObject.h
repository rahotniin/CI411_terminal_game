#pragma once

#include <string>

#include "int2.h"
#include "graphics.h"

// stores data representing an object in the game,
class GameObject {
public:
    std::string name;
    
    char symbol;
    int colour;

    Int2 pos;

    GameObject(std::string name, char symbol, int colour, Int2 pos) :
        pos(pos)
    {
        this->name = name;
        this->symbol = symbol;
        this->colour = colour;
    }
};