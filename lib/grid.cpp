#include <iostream>
#include <vector>
#include <raylib.h>
#include "grid.h"
#include "colors.h"
Grid::Grid(){
    numCols = 10;
    numRows = 20;
    cellSize = 30;
    Initalize();
    colors = GetCellColors();
}

void Grid::Initalize(){
    for (int row = 0; row < numRows; row++)
    {
        for(int cols = 0; cols < numCols;cols++){
            grid[row][cols] = 0;
        }
    }
    
}

void Grid::print(){
    for (int row = 0; row < numRows; row++)
    {
        for(int cols = 0; cols < numCols;cols++){
            std::cout<<grid[row][cols]<<" ";
        }
        std::cout<<std::endl;
    }
    
}

void Grid::Draw(){
    for(int row=0;row < numRows;row++){
        for (int cols = 0; cols < numCols; cols++)
        {
            int cellValue = grid[row][cols];
            DrawRectangle(cols*cellSize+11,row*cellSize+11,cellSize-1,cellSize-1,colors[cellValue]);
        }
        
    }
}

bool Grid::IsCellOutSide(int row, int column)
{
    if( row >= 0 && row < numRows  && column >= 0 && column < numCols){
        return false;
    }
    return true;
}

bool Grid::isCellEmpty(int row, int cols)
{
    if(grid[row][cols] == 0){
        return true;
    }
    return false;
}

int Grid::ClearFullRows()
{
    int completed = 0;
    for(int row = numRows-1;row>=0; row--){
        if(isRowFull(row)){
            ClearRow(row);
            completed++;
        }
        else if(completed > 0){
            MoveRowDown(row, completed);
        }
    }
    return completed;
}

bool Grid::isRowFull(int row)
{
    for(int column = 0;column < numCols;column++){
        if(grid[row][column] == 0){
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row)
{
    for(int colums = 0;colums < numCols; colums++){
        grid[row][colums] = 0;
    }
}


void Grid::MoveRowDown(int row, int numRows){
    for(int columns = 0;columns <numCols; columns++){
        grid[row + numRows][columns] = grid[row][columns];
        grid[row][columns] = 0; 
    }
}
