#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game{
    public:
        Game();
        ~Game();
        void Draw();
        void HandleInput();
        void MoveBlockDown();
        bool GameOver;
        int score;
        Music music;

    private:
        Block GetRandomBlock();
        std::vector<Block> GetAllBlocks();
        bool isBlockOutSide();
        void MoveBlockRight();
        void MoveBlockLeft();
        void RotateBlock();
        void LockBlock();
        bool BlockFits();
        void Reset();
        void UpdatScore(int linescleared, int moveDownPoints);
        Grid grid;
        std::vector<Block> blocks;
        Block currenBlock;
        Block nextBlock;
        Sound rotatesound;
        Sound clearsound;
};