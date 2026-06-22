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
    float centerX = game->GetScreenSize().x * 0.5f;

    int nameSize = 22;
    int scoreSize = 40;
    float nameY = 10;
    float scoreY = 38;
    float gap = 22;

    const char* playerOne = "PLAYER 1";
    const char* playerTwo = "PLAYER 2";
    DrawText(playerOne, centerX - gap - MeasureText(playerOne, nameSize), nameY, nameSize, RAYWHITE);
    DrawText(playerTwo, centerX + gap, nameY, nameSize, RAYWHITE);

    std::string leftScore = std::to_string(scoreLeft);
    std::string rightScore = std::to_string(scoreRight);

    const char* dash = "-";
    DrawText(dash, centerX - MeasureText(dash, scoreSize)/2, scoreY, scoreSize, RAYWHITE);
    DrawText(leftScore.c_str(), centerX - gap - MeasureText(leftScore.c_str(), scoreSize), scoreY, scoreSize, RAYWHITE);
    DrawText(rightScore.c_str(), centerX + gap, scoreY, scoreSize, RAYWHITE);
}
