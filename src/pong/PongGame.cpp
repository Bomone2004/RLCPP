#include "pong/PongGame.h"

void PongGame::Update(float DeltaTime){
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