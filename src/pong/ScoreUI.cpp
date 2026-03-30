#include "pong/ScoreUI.h"
#include "pong/PongGame.h"
#include <string> 
void ScoreUI::Start()
{

    PongGame* pG = dynamic_cast<PongGame*>(game);
    pG->SetScoreDelegate([this](int leftScore, int rightScore)
    {
        this->scoreLeft = leftScore;
        this->scoreRight = rightScore;
    });

    //first time
    scoreLeft = pG->GetPoints(0);
    scoreRight = pG->GetPoints(1);
}
void ScoreUI::Update(float DeltaTime)
{
    //MOVED IN START PART DEFINITION
    //PongGame* pG = dynamic_cast<PongGame*>(game);
    //scoreLeft = pG->GetPoints(0);
    //scoreRight = pG->GetPoints(1);
    // TODO 
    // QUESTA COSA QUI NON CI PIACE
    // a noi servirebbe qualcosa che legge l'aggiornamento della ui 
    // in sostanza ci servirebbe un delegate chiamato quando viene aggiornato il punteggio 
}

void ScoreUI::Draw()
{
    DrawText(std::to_string(scoreLeft).c_str(),position.x -50,position.y,50, RAYWHITE);
    DrawText(std::to_string(scoreRight).c_str(),position.x +50,position.y,50, RAYWHITE);
}
