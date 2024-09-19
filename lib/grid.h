#pragma once

#include <vector>
#include <raylib.h>

class Grid{
    public:
        Grid();
        void Initalize();
        void print();
        void Draw();
        bool IsCellOutSide(int row, int column);
        bool isCellEmpty(int row, int cols);
        int ClearFullRows();
        int grid[20][10];
    private:
        bool isRowFull(int row);
        void ClearRow(int row);
        void MoveRowDown(int row, int numRows);
        int numRows;
        int numCols;
        int cellSize;
        std::vector<Color> colors;
};