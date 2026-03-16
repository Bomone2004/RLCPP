#include "pong/PongGame.h"

const InputManager* PongGame::GetInputManager() const
{
    return inputManager.get();
}

void PongGame::InitGame()
{
    SetClearColor(BLACK);
    inputManager->BindKey(Action::MOVE_UP, KEY_W);
    inputManager->BindKey(Action::MOVE_DOWN, KEY_S);
    inputManager->BindKey(Action::MOVE_RIGHT, KEY_D);
    inputManager->BindKey(Action::MOVE_LEFT, KEY_A);

    for(auto& go : GameObjects)
    {
        if(!go->IsActive()) continue;

        go->Start();
    }
}

void PongGame::Update(float DeltaTime){

    inputManager->Update();
    
    for(auto& go : GameObjects){

        if(!go->IsActive()) continue;

        go->Update(DeltaTime);
    }
}

void PongGame::Draw(){
    Game::Draw();
    

    for(auto& go : GameObjects){
        if(!go->IsActive()) continue;

        go->Draw();
    }

}