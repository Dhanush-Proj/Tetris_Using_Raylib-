#pragma once
#include <vector>
#include <map>
#include "Position.h"
#include "colors.h"

class Block{
    public:
        Block();
        std::vector<Position> GetCellPositions();
        void Rotate();
        void UndoRotation();
        void Draw(int offsetx, int offsety);
        void Move(int rows, int columns);
        int id;
        std::map<int, std::vector<Position>>cells;
    private:
        int cellsize;
        int rotationState;
        std::vector<Color> color;
        int rowOffset;
        int columnOffset;
};