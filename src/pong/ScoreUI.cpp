#include "pong/ScoreUI.h"
#include "pong/PongGame.h"
#include <string> 
void ScoreUI::Start()
{
    PongGame* pG = dynamic_cast<PongGame*>(game);
    if(pG)
    {
        pG->ScoreChangeDelegate = [this](int leftS, int rightS)
        {
            this->UpdateScore(leftS, rightS);
        };
        //cpp 11 version 
        //pG->ScoreChangeDelegate = std::bind(&ScoreUI::UpdateScore, this, std::placeholders::_1, std::placeholders::_2);
    }
}
void ScoreUI::Update(float DeltaTime)
{

}

void ScoreUI::Draw()
{
    DrawText(std::to_string(scoreLeft).c_str(),position.x -50,position.y,50, RAYWHITE);
    DrawText(std::to_string(scoreRight).c_str(),position.x +50,position.y,50, RAYWHITE);
}

void ScoreUI::UpdateScore(int leftScore, int rightScore)
{
    scoreLeft = leftScore;
    scoreRight = rightScore;
}
