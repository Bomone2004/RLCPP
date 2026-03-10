#include "core/Game.h"

void Game::Run()
{
    while(!WindowShouldClose() && !shouldClose) 
    {
        float DeltaTime = GetFrameTime();

        //Update 
        Update(DeltaTime);

        //Draw
        Draw();
    }
}

void Game::Quit()
{
    shouldClose = true;
}

void Game::Update(float DeltaTime)
{

}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(clearColor);


    EndDrawing();
}

void Game::SetClearColor(Color cl){
    clearColor = cl;
}

FVector2 Game::GetScreenSize() const
{
    return ScreenSize;
}

