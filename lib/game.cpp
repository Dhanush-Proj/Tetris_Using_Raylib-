#include "game.h"
#include <random>

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currenBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    GameOver = false;
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("audio/music.mp3");
    PlayMusicStream(music);
    rotatesound = LoadSound("audio/rotate.mp3");
    clearsound = LoadSound("audio/clear.mp3");
}

Game::~Game(){
    UnloadSound(rotatesound);
    UnloadSound(clearsound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }

    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}
std::vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{

    grid.Draw();
    currenBlock.Draw(11,11);
    switch(nextBlock.id){
        case 3:nextBlock.Draw(255,280);
            break;
        case 4:nextBlock.Draw(255,280);
            break;
        default:
            nextBlock.Draw(270,270);
            break;

    }
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if(GameOver && keyPressed != 0){
        GameOver = false;
        Reset();
    }
    switch (keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        MoveBlockDown();
        UpdatScore(0,1);
        break;
    case KEY_UP:
        RotateBlock();
        break;
    }
}
void Game::MoveBlockLeft()
{
    if (!GameOver)
    {

        currenBlock.Move(0, -1);
        if (isBlockOutSide() || BlockFits() == false)
        {
            currenBlock.Move(0, 1);
        }
    }
}
void Game::MoveBlockRight()
{
    if (!GameOver)
    {

        currenBlock.Move(0, 1);
        if (isBlockOutSide() || BlockFits() == false)
        {
            currenBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown()
{
    if (!GameOver)
    {

        currenBlock.Move(1, 0);
        if (isBlockOutSide() || BlockFits() == false)
        {
            currenBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

bool Game::isBlockOutSide()
{
    std::vector<Position> tiles = currenBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellOutSide(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    if (!GameOver)
    {

        currenBlock.Rotate();
        if (isBlockOutSide() || BlockFits() == false)
        {
            currenBlock.UndoRotation();
        }
        else{
            PlaySound(rotatesound);
        }
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currenBlock.GetCellPositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.column] = currenBlock.id;
    }
    currenBlock = nextBlock;
    if (BlockFits() == false)
    {
        GameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowscleared = grid.ClearFullRows();
    if(rowscleared > 0){
        PlaySound(clearsound);
        UpdatScore(rowscleared,0);
    }
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currenBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.isCellEmpty(item.row, item.column) == false)
        {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid.Initalize();
    blocks = GetAllBlocks();
    currenBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdatScore(int linescleared, int moveDownPoints)
{
    switch(linescleared){
        case 1:
            score += 100;
            break;
        case 2:
            score +=300;
            break;
        case 3:
            score += 500;
            break;
        default:
            break;
    }
    score += moveDownPoints;
}
