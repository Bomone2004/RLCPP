#include "pong/ScoreUI.h"
#include "pong/PongGame.h"
#include <string> 
void ScoreUI::Start()
{

}
void ScoreUI::Update(float DeltaTime)
{
    PongGame* pG = dynamic_cast<PongGame*>(game);
    scoreLeft = pG->GetPoints(0);
    scoreRight = pG->GetPoints(1);
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
