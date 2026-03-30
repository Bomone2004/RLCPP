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
    if(endingGame){
        countDown-=DeltaTime;
        if(0>=countDown){
            shouldClose=true;
        }
    }else{
        Game::Update(DeltaTime);
    }
    
}

void PongGame::Draw(){
    
    
    
    if(endingGame){
        BeginDrawing();
        ClearBackground(clearColor);
        DrawText( "Winner:", ScreenSize.x *0.5f + 10 ,ScreenSize.y *0.5f +40,50, RAYWHITE);
        DrawText((P1Points>P2Points)?"Player1":"Player2",ScreenSize.x *0.5f + 10,ScreenSize.y *0.5f +70,50, RAYWHITE);
        EndDrawing();
    }else{
        Game::Draw();
    }
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
    

    NotifyScoreChanged();

    if(P1Points >= 5 || P2Points >= 5 ){
        NotifyGameEnd();
    }
}

//SCORE DELEGTATE PART
void PongGame::SetScoreDelegate(ScoreDelegate delegate)
{
    onScoreChanged = std::move(delegate);
}

void PongGame::NotifyGameEnd(){
    endingGame=true;
    countDown=5.f;
    /*shouldClose=true;
    if (onScoreEnd)
    {
        onScoreEnd();
    }*/
}
void PongGame::NotifyScoreChanged()
{
    if (onScoreChanged)
    {
        onScoreChanged(P1Points, P2Points);
    }
}