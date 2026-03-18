#include "pong/PongGame.h"
#include "core/Collider.h"
#include <string>

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

    // Dopo l'update di tutti i gameobject, controlliamo le collisioni
    CheckCollisions();
}

// Collisione Rect-Circle (AABB) tra Paddle e Ball
// Usa le funzioni definite in Collider.h (namespace AIV_Collision)
void PongGame::CheckCollisions(){
    if(!ball || !paddle) return;
    if(!ball->IsActive() || !paddle->IsActive()) return;

    // Costruiamo i collider a partire dai dati dei gameobject
    AIV_Collision::RectCollider paddleCol;
    paddleCol.position = paddle->GetPosition();
    paddleCol.extents = paddle->GetBounds(); // w, h del rettangolo

    AIV_Collision::CircleCollider ballCol;
    ballCol.position = ball->GetPosition();
    ballCol.radius = ball->GetRadius();

    // CheckCollision(RectCollider, CircleCollider):
    // Trova il punto piu` vicino al centro del cerchio sul rettangolo
    // Se la distanza dal centro e` minore del raggio -> collisione
    if(AIV_Collision::CheckCollision(paddleCol, ballCol)){
        // Invertiamo la velocita` X della ball (rimbalzo)
        FVector2 vel = ball->GetVelocity();
        vel.x *= -1;
        ball->SetVelocity(vel);

        // Riposizionamento della ball fuori dal paddle
        // per evitare collisioni multiple nello stesso frame
        FVector2 pos = ball->GetPosition();
        if(vel.x > 0){
            pos.x = paddleCol.position.x + paddleCol.extents.x + ballCol.radius + 1;
        } else {
            pos.x = paddleCol.position.x - ballCol.radius - 1;
        }
        ball->SetPosition(pos);
    }
}

void PongGame::Draw(){
    Game::Draw();

    for(auto& go : GameObjects){
        if(!go->IsActive()) continue;

        go->Draw();
    }

    // UI: Disegna il punteggio al centro-alto dello schermo
    // DrawText(const char* text, int posX, int posY, int fontSize, Color color)
    std::string score = std::to_string(scoreLeft) + " - " + std::to_string(scoreRight);
    DrawText(score.c_str(), GetScreenSize().x / 2 - 20, 10, 20, RAYWHITE);
}