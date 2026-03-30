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
    
    inputManager->BindKey(Action::MOVE_UP_P2, KEY_UP);
    inputManager->BindKey(Action::MOVE_DOWN_P2, KEY_DOWN);
    inputManager->BindKey(Action::MOVE_RIGHT_P2, KEY_RIGHT);
    inputManager->BindKey(Action::MOVE_LEFT_P2, KEY_LEFT);

    P1Points = 0;
    P2Points = 0;
    Game::InitGame();
}

void PongGame::Update(float DeltaTime)
{
    Game::Update(DeltaTime);
}

void PongGame::Draw(){

    Game::Draw();
}
int PongGame::GetPoints(int playerIndex) const { 
    return (playerIndex==0)?P1Points:P2Points;
}

void PongGame::ScorePoints(int playerIndex)
{
    if(playerIndex == 0){
        P1Points++;
    }
    else{
        P2Points++;
    }

    if(ScoreChangeDelegate)
    {
        ScoreChangeDelegate(P1Points, P2Points);
    }

}

