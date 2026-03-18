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

void Game::InitGame()
{
    for(auto& go : GameObjects)
    {
        if(!go->IsActive()) continue;

        go->Start();
        collisionManager->RegisterCollider(go);
    }
}

void Game::Update(float DeltaTime)
{
    inputManager->Update();
    for(auto& go : GameObjects)
    {   
        if(!go->IsActive()) continue;
        go->Update(DeltaTime);
    }
    collisionManager->Update();
    
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(clearColor);

    for(auto& go : GameObjects){
        if(!go->IsActive()) continue;

        go->Draw();
    }

    EndDrawing();
}

void Game::SetClearColor(Color cl){
    clearColor = cl;
}

FVector2 Game::GetScreenSize() const
{
    return ScreenSize;
}

