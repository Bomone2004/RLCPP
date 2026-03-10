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
    ClearBackground(RAYWHITE);

    DrawText("Hello Ray!", 300, 200, 30, GREEN);

    EndDrawing();
}

FVector2 Game::GetScreenSize() const
{
    return ScreenSize;
}

