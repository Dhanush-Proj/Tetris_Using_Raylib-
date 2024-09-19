#include <raylib.h>
#include "lib/game.h"
#include "lib/colors.h"
#include <iostream>

double LastUpdatTime = 0;

bool EventTriggered(double interval){
    double currentTime = GetTime();
    if(currentTime - LastUpdatTime >= interval){
        LastUpdatTime = currentTime;
        return true;
    }
    return false;
}

int main(){
    
    int ScreenWidth = 500;
    int ScreenHeight = 620;

    InitWindow(ScreenWidth,ScreenHeight,"Raylib Tetris");
    SetTargetFPS(60);
    Font font = LoadFontEx("fonts/monogram.ttf",64,0,0);

    // block.Move(4,3);
    Game game = Game();
    while (!WindowShouldClose())
    {
        UpdateMusicStream(game.music);
        game.HandleInput();
        if(EventTriggered(0.3)){
            game.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(darkblue);
        DrawTextEx(font,"Score",{365, 15},38,2,WHITE);
        DrawTextEx(font,"Next",{370, 175},38,2,WHITE);
        if(game.GameOver){
            DrawTextEx(font,"GAME OVER",{320, 450},38,2,WHITE);
        }
        DrawRectangleRounded({320,55,170,60},0.3,6,lightblue);

        char scoretext[10];
        sprintf(scoretext,"%d",game.score);
        Vector2 textsize = MeasureTextEx(font,scoretext,38,2);
        
        DrawTextEx(font,scoretext,{320 + (170 - textsize.x)/2, 65},38,2,WHITE);
        DrawRectangleRounded({320,215,170,180},0.3,6,lightblue);
        game.Draw();
        EndDrawing();
    }
    CloseWindow();


}